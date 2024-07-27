import cv2
from ultralytics import YOLO
import serial

port = "/dev/ttyTHS1"
baud_rate = 115200
timeout = 1
ser = serial.Serial(port, baud_rate, timeout=timeout)

model = YOLO("best.pt")
cap = cv2.VideoCapture('/dev/video0')

while cap.isOpened():
    success, frame = cap.read()

    if success:
        if results:
            detection = results[0].boxes[0]
            class_name = detection.cls  # 获取类别名称
            confidence = detection.conf  # 获取置信度
            
            # 根据类别名称发送不同的数据
            if class_name == 'waste':
                ser.write(b'0'.encode())
            elif class_name == 'duanzi' or class_name == 'sandbag':
                ser.write(b'1'.encode())

        results = model.track(frame, persist=True)
        annotated_frame = results[0].plot()

        cv2.imshow("YOLOv8", annotated_frame)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break


ser.close()
cap.release()
cv2.destroyAllWindows()