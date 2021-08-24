class MyClass:

    """Docstring for MyClass. """
    i = 1
    def __init__(self):
        """类的实例化操作会自动调用 """
        self.a = 1
        self.b = 1
    def f(self ):
        """类的方法"""
        return "hello"
    def ptr(self):
        print(self)
        print(self.__class__)
x = MyClass()
print("MyClass.i",x.i)
print("MyClass.f()",x.f())
print("MyClass.a",x.a)
x.ptr()
