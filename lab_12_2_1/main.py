from ctypes import *

try:
    lib = cdll.LoadLibrary("./libarr.so")
except Exception as e:
    print("Could not load library:", e)

num = 17
size = sizeof(c_int)

arr = c_void_p(0)
lib.create_array(num, size, byref(arr))
arr = cast(arr, POINTER(c_int))

for i in range(num):
    arr[i] = i

lib.print_int_array(num, arr)
lib.offset_array(2, num, size, arr)
lib.print_int_array(num, arr)

arr2 = c_void_p(0)
num2 = c_int(0)
lib.copy_int_array(num, arr, byref(num2), byref(arr2))
lib.print_int_array(num2, arr2)

lib.delete_array(byref(arr))
