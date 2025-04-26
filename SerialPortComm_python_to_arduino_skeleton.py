# import serial library
import serial, time

# use port device from Arduino app; you must uncomment the appropriate port line
# if on OSX, the port will look like (get NNNN from the Arduino IDE):
# port = "/dev/cu.usbmodemNNNN"

# if on Windows, the port will look like (get N from the Arduino IDE):
port = "/dev/ttyUSB1"

# create serial port object called arduinoSerialData
arduinoSerialData = serial.Serial(port, 9600)

# flush buffer
if arduinoSerialData.inWaiting() > 0:
    print(arduinoSerialData.readline().decode())

while True:
    cmd = input("Enter command: ")

    if cmd == "b":
        break

    else:
        bytes_sent = arduinoSerialData.write(cmd.encode())

        time.sleep(1)

        if arduinoSerialData.inWaiting() > 0:
            while bytes_sent != 0:
                print(arduinoSerialData.readline().decode())
                bytes_sent -= 1

