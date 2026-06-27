import serial
import serial.tools.list_ports
import time

def active_ports():
    ports = serial.tools.list_ports.comports();
    # print(ports)
    for p in ports:
        print(f"{p.device} \n {p.description}")

    return p.device

def serial_data(port_name,baud_rate,timeout=1):
    try:
        with serial.Serial(port=port_name,baudrate=baud_rate,timeout=timeout) as ser:
            ser.reset_input_buffer()

            while True:
                if ser.in_waiting>0:
                    data = ser.readline();

                    data = data.decode("utf-8", errors="ignore").strip()

                    print(data)

                    time.sleep(0.1)
    except serial.SerialException as e:
        print(f"Couldn't open port {e}")
    except KeyboardInterrupt:
        print("User Interrupt")

if __name__=="__main__":
    p = active_ports();
    serial_data(p,9600)
