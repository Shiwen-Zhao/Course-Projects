import sys
import cv2
import torch
from PySide6 import QtWidgets, QtGui
from PySide6.QtWidgets import QApplication, QMainWindow, QFileDialog, QLabel, QVBoxLayout, QWidget, QPushButton
from PySide6.QtGui import QImage, QPixmap
from PySide6.QtCore import Qt
from detect_plate import load_model, init_model, detect_Recognition_plate, draw_result  # 导入您的YOLOv5代码

class LicensePlateRecognitionApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("License Plate Recognition")
        self.setGeometry(100, 100, 800, 600)

        self.label = QLabel(self)
        self.label.setAlignment(Qt.AlignCenter)

        self.button = QPushButton("Load Image", self)
        self.button.clicked.connect(self.load_image)

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.button)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)

        # 加载模型
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.detect_model = load_model('weights/plate_detect.pt', self.device)
        self.plate_rec_model = init_model(self.device, 'weights/plate_rec_color.pth', is_color=False)

    def load_image(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        file_name, _ = QFileDialog.getOpenFileName(self, "Open Image File", "", "Images (*.png *.xpm *.jpg);;All Files (*)", options=options)
        if file_name:
            image = cv2.imread(file_name)
            results = detect_Recognition_plate(self.detect_model, image, self.device, self.plate_rec_model, img_size=640, is_color=False)
            image_with_results = draw_result(image, results)

            # OpenCV to QImage
            height, width, channel = image_with_results.shape
            bytes_per_line = 3 * width
            q_img = QImage(image_with_results.data, width, height, bytes_per_line, QImage.Format_RGB888).rgbSwapped()

            # Set QImage to QLabel
            self.label.setPixmap(QPixmap.fromImage(q_img))
            self.label.adjustSize()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LicensePlateRecognitionApp()
    window.show()
    sys.exit(app.exec())
