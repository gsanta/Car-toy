Import("env")

# Improve Nano upload reliability by pulsing DTR/RTS just before avrdude.
def pre_upload_reset(source, target, env):
    port = env.get("UPLOAD_PORT")
    if not port:
        return

    try:
        import time
        import serial

        ser = serial.Serial(port=port, baudrate=1200, timeout=0.2)
        ser.dtr = False
        ser.rts = False
        time.sleep(0.05)
        ser.dtr = True
        ser.rts = True
        time.sleep(0.05)
        ser.close()
        print("[pre_upload_reset] Pulsed DTR/RTS on {}".format(port))
        time.sleep(0.2)
    except Exception as exc:
        print("[pre_upload_reset] Skipped: {}".format(exc))


env.AddPreAction("upload", pre_upload_reset)
