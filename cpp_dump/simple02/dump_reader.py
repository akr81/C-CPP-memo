import ctypes


class InnerStruct(ctypes.Structure):
    _fields_ = [("inner01", ctypes.c_float), ("inner02", ctypes.c_uint16)]


class SimpleStruct(ctypes.Structure):
    _fields_ = [("member_int01", ctypes.c_int), ("member_int02", ctypes.c_int),
                ("member_int03", ctypes.c_int), ("member_uint8", ctypes.c_uint8),
                ("member_uint16", ctypes.c_uint16), ("member_uint32", ctypes.c_uint32),
                ("member_uint64", ctypes.c_uint64), ("member_size", ctypes.c_size_t),
                ("member_bool01", ctypes.c_bool), ("member_double01", ctypes.c_double),
                ("inner", InnerStruct)]


# DLLをロード
dll = ctypes.cdll.LoadLibrary("./dll_sample.dll")

# 構造体のインスタンスを生成
simple = SimpleStruct()

# dllの値詰め込み関数を実行
dll.FillDumpData(ctypes.byref(simple))

# 構造体の中身を確認
for field in simple._fields_:
    print(getattr(simple, field[0]))
