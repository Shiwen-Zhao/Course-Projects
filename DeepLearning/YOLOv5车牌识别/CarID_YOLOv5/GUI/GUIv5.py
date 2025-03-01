import sys
import cv2
import torch
from PySide6.QtWidgets import QApplication, QMainWindow, QFileDialog, QLabel, QVBoxLayout, QWidget, QPushButton, \
    QTextEdit
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

        self.textbox = QTextEdit(self)
        self.textbox.setReadOnly(True)  # 设置文本框为只读

        self.button_load = QPushButton("Load Image", self)
        self.button_load.clicked.connect(self.load_image)

        self.button_save = QPushButton("Save Image", self)
        self.button_save.clicked.connect(self.save_image)
        self.button_save.setEnabled(False)  # 初始时禁用保存按钮

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.textbox)
        layout.addWidget(self.button_load)
        layout.addWidget(self.button_save)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)

        # 加载模型
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.detect_model = load_model('weights/plate_detect.pt', self.device)
        self.plate_rec_model = init_model(self.device, 'weights/plate_rec_color.pth', is_color=False)

        self.processed_image = None  # 用于存储处理后的图像

    def load_image(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        file_name, _ = QFileDialog.getOpenFileName(self, "Open Image File", "",
                                                   "Images (*.png *.xpm *.jpg);;All Files (*)", options=options)
        if file_name:
            image = cv2.imread(file_name)
            results = detect_Recognition_plate(self.detect_model, image, self.device, self.plate_rec_model,
                                               img_size=640, is_color=False)

            # Debug: 打印识别结果
            print("Recognition Results:", results)

            self.processed_image = draw_result(image, results)

            # 显示图像到QLabel
            height, width, channel = self.processed_image.shape
            bytes_per_line = 3 * width
            q_img = QImage(self.processed_image.data, width, height, bytes_per_line, QImage.Format_RGB888).rgbSwapped()
            self.label.setPixmap(QPixmap.fromImage(q_img))
            self.label.adjustSize()

            # 显示识别结果到文本框
            if results:
                plate_text = "\n".join([result['plate'] for result in results if 'plate' in result])
                print("Plate Text:", plate_text)  # Debug: 打印将要显示的车牌文本
                self.textbox.setPlainText(plate_text)
            else:
                self.textbox.setPlainText("No license plate detected.")

            self.button_save.setEnabled(True)  # 处理完毕后启用保存按钮

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
