import sys
import cv2
import torch
from PySide6.QtWidgets import QApplication, QMainWindow, QFileDialog, QLabel, QVBoxLayout, QWidget, QPushButton
from PySide6.QtGui import QImage, QPixmap
from PySide6.QtCore import Qt
from detect_plate import load_model, init_model, detect_Recognition_plate, draw_result


class LicensePlateRecognitionApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("License Plate Recognition")
        self.setGeometry(100, 100, 800, 600)

        self.label = QLabel(self)
        self.label.setAlignment(Qt.AlignCenter)

        self.button_load = QPushButton("加载图片", self)
        self.button_load.clicked.connect(self.load_image)

        self.button_save = QPushButton("保存图片", self)
        self.button_save.clicked.connect(self.save_image)
        self.button_save.setEnabled(False)

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.button_load)
        layout.addWidget(self.button_save)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)

        # 加载模型
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.detect_model = load_model('weights/plate_detect.pt', self.device)
        self.plate_rec_model = init_model(self.device, 'weights/plate_rec_color.pth', is_color=False)

        self.processed_image = None

    def load_image(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        file_name, _ = QFileDialog.getOpenFileName(self, "Open Image File", "",
                                                   "Images (*.png *.xpm *.jpg);;All Files (*)", options=options)
        if file_name:
            image = cv2.imread(file_name)
            results = detect_Recognition_plate(self.detect_model, image, self.device, self.plate_rec_model,
                                               img_size=640, is_color=False)
            self.processed_image = draw_result(image, results)

            # OpenCV to QImage
            height, width, channel = self.processed_image.shape
            bytes_per_line = 3 * width
            q_img = QImage(self.processed_image.data, width, height, bytes_per_line, QImage.Format_RGB888).rgbSwapped()

            # Set QImage to QLabel
            self.label.setPixmap(QPixmap.fromImage(q_img))
            self.label.adjustSize()

            self.button_save.setEnabled(True)

    def save_image(self):
        if self.processed_image is not None:
            options = QFileDialog.Options()
            file_name, _ = QFileDialog.getSaveFileName(self, "Save Image File", "",
                                                       "Images (*.png *.jpg *.bmp);;All Files (*)", options=options)
            if file_name:
                cv2.imwrite(file_name, self.processed_image)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LicensePlateRecognitionApp()
    window.show()
    sys.exit(app.exec())
