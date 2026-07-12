
//Дырявая функция
[[noreturn]] 
static int func()
{
    if (true) return 34;
}

[[deprecated("is deprecated! Use \'new_func()\'.")]] 
static void old_func() {}
static void new_func() {}

[[nodiscard]]
static int get_zero()
{
    return 0;
}

// Не используемый параметр функции.
static int func2( [[maybe_unused]] int value1, int value2)
{
    value2 *= 2;
    return value2;
}

int main()
{
    func(); // warning - function declared with 'noreturn' has a return statement

    //old_func();   // Error - old_func() is deprecated!
    new_func();     // correct

    //get_zero();           // warning - return value ignored
    int i = get_zero();     // correct

    int i2 = func2(10, 15); //

    return 0;
}