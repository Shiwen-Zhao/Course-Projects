import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QPushButton, QFileDialog, QVBoxLayout, QWidget
from PyQt5.QtGui import QPixmap, QImage
from PyQt5.QtCore import Qt
import cv2
import torch
import numpy as np
from models.experimental import attempt_load
from utils.general import non_max_suppression, scale_coords
from utils.datasets import letterbox
from utils.torch_utils import select_device

class LicensePlateRecognitionApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.device = select_device('cpu')  # 自动选择设备
        self.model = self.load_model()

    def initUI(self):
        self.setWindowTitle("车牌识别系统")
        self.setGeometry(100, 100, 800, 600)

        # 使用布局管理器
        layout = QVBoxLayout()

        self.label = QLabel(self)
        self.label.setAlignment(Qt.AlignCenter)
        self.label.setFixedSize(640, 480)
        self.label.setText("选择一张图片进行车牌识别")
        layout.addWidget(self.label)

        self.load_button = QPushButton("加载图片", self)
        self.load_button.clicked.connect(self.load_image)
        layout.addWidget(self.load_button)

        self.detect_button = QPushButton("识别车牌", self)
        self.detect_button.clicked.connect(self.detect_plate)
        layout.addWidget(self.detect_button)

        # 设置中央窗口和布局
        central_widget = QWidget()
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

    def load_image(self):
        options = QFileDialog.Options()
        file_path, _ = QFileDialog.getOpenFileName(self, "选择图片", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)",
                                                   options=options)
        if file_path:
            self.img = cv2.imread(file_path)
            self.display_image()

    def display_image(self):
        img_rgb = cv2.cvtColor(self.img, cv2.COLOR_BGR2RGB)
        img_height, img_width, img_channel = img_rgb.shape
        q_img = QImage(img_rgb.data, img_width, img_height, img_channel * img_width, QImage.Format_RGB888)
        pixmap = QPixmap.fromImage(q_img)
        pixmap = pixmap.scaled(640, 480, Qt.KeepAspectRatio)
        self.label.setPixmap(pixmap)

    def load_model(self):
        model_path = '../weights/plate_detect.pt'  # 替换为你的 yolov5 模型路径
        model = attempt_load(model_path, map_location=self.device)
        return model

    def detect_plate(self):
        if hasattr(self, 'img'):
            img = letterbox(self.img, new_shape=640)[0]
            img = img[:, :, ::-1].transpose(2, 0, 1)
            img = np.ascontiguousarray(img)

            img = torch.from_numpy(img).to(self.device)
            img = img.float() / 255.0
            if img.ndimension() == 3:
                img = img.unsqueeze(0)

            with torch.no_grad():
                pred = self.model(img)[0]
                pred = non_max_suppression(pred, 0.25, 0.45, classes=None, agnostic=False)

            for det in pred:
                if len(det):
                    det[:, :4] = scale_coords(img.shape[2:], det[:, :4], self.img.shape).round()

                    for *xyxy, conf, cls in reversed(det):
                        label = f'{conf:.2f}'
                        xyxy = torch.tensor(xyxy).view(-1).tolist()
                        # 改变矩形框的颜色为蓝色，并调整线条粗细
                        cv2.rectangle(self.img, (int(xyxy[0]), int(xyxy[1])), (int(xyxy[2]), int(xyxy[3])), (255, 0, 0), 3)
                        # 改变文本的颜色为红色，并增大字号
                        cv2.putText(self.img, label, (int(xyxy[0]), int(xyxy[1]) - 2), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 3)
            self.display_image()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = LicensePlateRecognitionApp()
    mainWindow.show()
    sys.exit(app.exec_())
