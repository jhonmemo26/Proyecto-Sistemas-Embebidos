from fastapi import FastAPI, Request
from fastapi.responses import FileResponse

from openai import OpenAI

from dotenv import load_dotenv

import tempfile
import os

#==================================================
# LOAD ENV
#==================================================

load_dotenv()

#==================================================
# FASTAPI
#==================================================

app = FastAPI()

#==================================================
# OPENAI
#==================================================

client = OpenAI(
    api_key="mi"
)

#==================================================
# ROOT
#==================================================

@app.get("/")
async def root():

    return {
        "status": "server working"
    }

#==================================================
# GENERATE GREETING
#==================================================

@app.get("/generate_greeting")
async def generate_greeting():

    print("\n========================")
    print("GENERATING GREETING")
    print("========================")

    greeting = (
        "Hola. "
        "Soy Craibot. "
        "¿En qué te puedo ayudar?"
    )

    tts = client.audio.speech.create(

        model="gpt-4o-mini-tts",

        voice="nova",

        input=greeting,

        response_format="pcm"
    )

    with open("response.pcm", "wb") as f:

        f.write(tts.content)

    print("GREETING READY")

    return {
        "status": "ok"
    }

#==================================================
# UPLOAD AUDIO
#==================================================

@app.post("/upload")
async def upload_audio(request: Request):

    #==============================================
    # RECEIVE WAV
    #==============================================

    audio_bytes = await request.body()

    print("\n========================")
    print("WAV RECEIVED")
    print("========================")

    #==============================================
    # SAVE TEMP WAV
    #==============================================

    with tempfile.NamedTemporaryFile(
        delete=False,
        suffix=".wav"
    ) as tmp:

        tmp.write(audio_bytes)

        temp_filename = tmp.name

    print("TEMP FILE:", temp_filename)

    #==============================================
    # WHISPER
    #==============================================

    with open(temp_filename, "rb") as audio_file:

        transcript = client.audio.transcriptions.create(
            model="whisper-1",
            file=audio_file
        )

    text = transcript.text.lower()

    print("\n========================")
    print("USER SAID:")
    print(text)
    print("========================")

    #==============================================
    # GPT RESPONSE
    #==============================================

    completion = client.chat.completions.create(

        model="gpt-4.1-mini",

        messages=[

            {
                "role": "system",

                "content":
                (
                    "Eres Craibot, un robot físico "
                    "amigable creado por estudiantes "
                    "de ingeniería. "
                    "Responde de manera corta, clara, "
                    "natural y útil. "
                    "Tus respuestas deben ser breves "
                    "porque serán habladas por voz. "
                    "Habla siempre en español."
                )
            },

            {
                "role": "user",

                "content": text
            }
        ]
    )

    response = (
        completion
        .choices[0]
        .message
        .content
    )

    print("\n========================")
    print("GPT RESPONSE:")
    print(response)
    print("========================")

    #==============================================
    # CREATE PCM TTS
    #==============================================

    tts = client.audio.speech.create(

        model="tts-1",

        voice="alloy",

        input=response,

        response_format="pcm"
    )

    #==============================================
    # SAVE PCM
    #==============================================

    with open("response.pcm", "wb") as f:

        f.write(tts.content)

    #==============================================
    # DEBUG
    #==============================================

    pcm_size = os.path.getsize(
        "response.pcm"
    )

    print("\n========================")
    print("PCM GENERATED")
    print("PCM SIZE:", pcm_size)
    print("========================")

    #==============================================
    # RETURN JSON
    #==============================================

    return {
        "text": response
    }

#==================================================
# TTS DOWNLOAD
#==================================================

@app.get("/tts")
async def get_tts():

    print("\n========================")
    print("ESP32 REQUESTED TTS")
    print("========================")

    if not os.path.exists("response.pcm"):

        print("ERROR: response.pcm NOT FOUND")

        return {
            "error": "pcm file not found"
        }

    print(
        "SENDING PCM SIZE:",
        os.path.getsize("response.pcm")
    )

    return FileResponse(

        "response.pcm",

        media_type="application/octet-stream"
    )