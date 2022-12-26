import ctypes, process
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog, QMessageBox
from interface import Ui_MainWindow

class my_window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.function_shift = None
        self.function_squares = None
        self.array = []
        self.shift = 0
        
        """Соотношение сигналов и слотов"""
        self.ui.pushButton.clicked.connect(self.left_shift)
        self.ui.pushButton_2.clicked.connect(self.full_squares)

    """Установление функции сдвига"""
    def set_left_shift(self, function):
        self.function_shift = function

    """Установление функции получения полных квадратов"""
    def set_full_squares(self, function):
        self.function_squares = function

    """Создание оповещения"""
    def create_message(self, text):
        msg = QMessageBox()
        msg.setText(text)
        msg.exec()

    """Валидация массива"""
    def set_array(self):
        text_array = self.ui.lineEdit.text()

        rc, self.array = process.get_array(text_array)

        if rc != 0:
            self.create_message("На ввод должны подаваться исключительно целые числа")

    """Валидация сдвига"""
    def set_shift(self):
        text_shift = self.ui.lineEdit_2.text()

        if text_shift.isdigit():
            self.shift = int(text_shift)
        else:
            self.create_message("Сдвиг задается целым положительным числом")
            

    """Сдвиг массива влево"""
    def left_shift(self):
        self.set_array()
        self.set_shift()

        if self.shift > 0 and len(self.array) != 0:
            rc, new_array = process.left_k_shift(self.array, self.shift, self.function_shift)

            if rc == 0:
                self.ui.lineEdit_3.setText(" ".join([str(x) for x in new_array]))
            else:
                self.create_message("Ошибка сдвига")

    def full_squares(self):
        self.set_array()

        if len(self.array) != 0:
            rc, new_array = process.get_full_squares(self.array, self.function_squares)

            if rc == 0:
                self.ui.lineEdit_3.setText(" ".join([str(x) for x in new_array]))
            else:
                self.create_message("Ошибка получения полных квадратов")



"""Запуск приложения"""
def main():
    lib = ctypes.CDLL("libarr.so")

    #int left_k_shift(int *arr, int size, int k);
    #int get_full_squares(int *src_array, int src_size, int *dst_array, int *dst_size);

    _left_k_shift = lib.left_k_shift
    _left_k_shift.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
    _left_k_shift.restype = ctypes.c_int

    _get_full_squares = lib.get_full_squares
    _get_full_squares.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int))
    _get_full_squares.restype = ctypes.c_int

    app = QApplication([])

    window = my_window()
    window.show()

    window.set_left_shift(_left_k_shift)
    window.set_full_squares(_get_full_squares)

    app.exec()

if __name__ == '__main__':
    main()