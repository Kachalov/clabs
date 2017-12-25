from ctypes import *

try:
    lib = cdll.LoadLibrary("./libarr.so")
except Exception as e:
    print("Could not load library:", e)
    exit()

num = 17
size = sizeof(c_int)

lib.error_msg.restype = POINTER(c_char)

def error_msg(err):
    print("%s #%d" % (cast(lib.error_msg(err), c_char_p).value.decode("utf-8"), err))

arr = c_void_p(0)
arr = cast(arr, POINTER(c_int))
err = lib.create_array(num, size, byref(arr))
if (err):
    error_msg(err)
    exit()

for i in range(num):
    arr[i] = i

lib.print_int_array(num, arr)
lib.offset_array(2, num, size, arr)
lib.print_int_array(num, arr)

arr2 = c_void_p(0)
num2 = c_int(0)
err = lib.copy_int_array(num, arr, byref(num2), byref(arr2))
if (err):
    error_msg(err)
    exit()

lib.print_int_array(num2, arr2)

lib.delete_array(byref(arr))
