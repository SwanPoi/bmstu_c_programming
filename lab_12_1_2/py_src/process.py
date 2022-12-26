import ctypes

def get_array(string):
    error = 0
    array = []

    buffer = list(string.split())

    for element in buffer:
        if element.isdigit():
            array.append(int(element))
        else:
            error += 1

    return error, array

def left_k_shift(array, shift, _left_k_shift):
    src_len = len(array)
    src = (ctypes.c_int * src_len)(*array)

    rc = _left_k_shift(src, src_len, shift)

    return rc, list(src)

def get_full_squares(array, _get_full_squares):
    answer = []

    src_len = len(array)
    src = (ctypes.c_int * src_len)(*array)
    dst_len = ctypes.c_int(0)

    rc = _get_full_squares(src, src_len, None, dst_len)

    if rc == 0:
        dst = (ctypes.c_int * dst_len.value)()

        rc = _get_full_squares(src, src_len, dst, dst_len)

        answer = dst
    
    return rc, list(answer)


def main():
    lib = ctypes.CDLL("../libarr.so")

    #int left_k_shift(int *arr, int size, int k);
    #int get_full_squares(int *src_array, int src_size, int *dst_array, int *dst_size);

    _left_k_shift = lib.left_k_shift
    _left_k_shift.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
    _left_k_shift.restype = ctypes.c_int

    _get_full_squares = lib.get_full_squares
    _get_full_squares.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int))
    _get_full_squares.restype = ctypes.c_int

    string = input()

    rc, array = get_array(string)

    if rc == 0:

        print(left_k_shift(array, 2, _left_k_shift))

        print(get_full_squares(array, _get_full_squares))

if __name__ == '__main__':
    main()

