Программа решает задачу отыскания решения системы линейных уравнений методом Гаусса-Жордана с выбором главного элемента по столбцу.

Использование программы:
    lss [input_filename] [output_filename] [options]
    Опции включают:
        -d      печать отладочных сообщений [по умолчанию НЕТ]
        -e      печать ошибок [по умолчанию НЕТ]
        -p      печать матрицы [по умолчанию НЕТ]
        -t      печать времени выполнения программы [по умолчанию НЕТ]
        -h, -?  печать справки и выход
    По умолчанию имя входного файла - lss_01_05_in.txt, имя выходного файла - lss_01_05_out.txt.

Программа состоит из двух модулей:
    интерфейсного, находящегося в файле main_lss_01_05.c;
    вычислительного, находящегося в файле lss_01_05.c.

В интерфейсном модуле реализованы следующие функции:
    void exception(int code, const char *message)
        Обработка ошибок: функция печатает сообщение об ошибке и завершает программу с возвратом кода ошибки.
        Коды и описания ошибок:
            2: Ошибка: Некорректный синтаксис параметров командной строки. Такого параметра не существует
            3: Ошибка: Некорректный синтаксис параметров командной строки. Параметров, определяемых как имена файлов, слишком много (более двух)
            4: Ошибка: Некорректная очередность параметров командной строки
            5: Ошибка: Такого файла не существует
            6: Ошибка: Файл пуст
            7: Ошибка: Значение n не является положительным целым числом
            8: Ошибка: Недостаточно элементов в матрице
            9: Ошибка: Элемент матрицы не является числом или значение n не является положительным целым числом
        ------------------------------
        Параметры:
            code: целое число - код ошибки
            message: указатель на неизменяемый символ - описание ошибки
        ------------------------------
        Возвращаемые значения (нет)

    int string_length(const char *string)
        Подсчет длины массива символов.
        ------------------------------
        Параметры:
            string: указатель на неизменяемый символ - массив символов
        ------------------------------
        Возвращаемые значения (целое число):
            Количество символов в массиве string

    int file_exists(const char *filename)
        Проверка существования файла с заданным именем.
        ------------------------------
        Параметры:
            filename: указатель на неизменяемый символ - имя файла (путь к файлу)
        ------------------------------
        Возвращаемые значения (целое число):
            0: Файла с таким именем не существует
            1: Файл с таким именем существует

    void validate_params(int argc, char *argv[], char **input_filename, char **output_filename)
        Валидация параметров командной строки, присваивание заданных в параметрах командной строки имен входного и выходного файла переменным input_filename и output_filename соответственно: при обнаружении ошибки в синтаксисе или очередности параметров командной строки данная функция вызывает функцию exception, передавая в качестве аргументов код ошибки и описание ошибки.
        ------------------------------
        Параметры:
            argc: целое число - количество аргументов командной строки
            argv: массив указателей на символы - аргументы командной строки
            input_filename: указатель на указатель на символ - имя входного файла
            output_filename: указатель на указатель на символ - имя выходного файла
        ------------------------------
        Возвращаемые значения (нет)

    void input(const char *input_filename, double **A, double **B, int *n)
        Считывание значения n из входного файла, выделение памяти для массивов A и B, считывание значений элементов матрицы A и вектора B из входного файла, проверка корректности входных значений: при обнаружении некорректных входных значений данная функция вызывает функцию exception, передавая в качестве аргументов код ошибки и описание ошибки.
        ------------------------------
        Параметры:
            input_filename: указатель на неизменяемый символ - имя входного файла
            A: указатель на указатель на вещественное число - матрица A
            B: указатель на указатель на вещественное число - вектор B
            n: целое число - размерность матрицы A и вектора B
        ------------------------------
        Возвращаемые значения (нет)

    void print_help()
        Печать краткого руководства по использованию программы.
        ------------------------------
        Параметры (нет)
        ------------------------------
        Возвращаемые значения (нет)

    void print_matrix(int n, double *A, double *B)
        Печать матрицы A и вектора B.
        ------------------------------
        Параметры:
            n: целое число - размерность матрицы A и вектора B
            A: указатель на вещественное число - матрица A
            B: указатель на вещественное число - вектор B
        ------------------------------
        Возвращаемые значения (нет)

    void output(const char *output_filename, int result, int n, const double *X)
        Запись решения X (если решение системы существует) или 0 (если решения системы не существует) в выходной файл.
        ------------------------------
        Параметры:
            output_filename: указатель на неизменяемый символ - имя выходного файла
            result: целое число - значение, возвращенное функцией lss_01_05
            n: целое число - размерность матрицы A и вектора B
            X: указатель на неизменяемое вещественное число - вектор решения X
        ------------------------------
        Возвращаемые значения (нет)

В вычислительном модуле реализованы следующие функции:
    size_t lss_memsize_01_05(int n)
        Определение размера дополнительной памяти, требуемой методу: размер дополнительной памяти определяется как произведение n и размера типа double.
        ------------------------------
        Параметры:
            n: целое число - размерность матрицы A и вектора B
        ------------------------------
        Возвращаемые значения (неотрицательное целое число):
            Размер дополнительной памяти

    int lss_01_05(int n, double *A, double *B, double *X, double *tmp)
        Решение задачи отыскания решения системы линейных уравнений методом Гаусса-Жордана:
            Элементы массива, хранящего порядок переменных в ответе, инициализируются значениями -1 (для этого массива требуется дополнительная память tmp).
            Осуществляется проход по строкам и столбцам матрицы A:
                Происходит выбор главного элемента по столбцу: выбор осуществляется среди коэффициентов матрицы A при неизвестной рассматриваемого в текущий момент столбца матрицы A, главным элементом по столбцу считается наибольший по модулю коэффициент матрицы A при этой неизвестной. Если в столбце все строки, начиная с текущей рассматриваемой, содержат нули, то текущий рассматриваемый столбец пропускается без увеличения номера текущей строки.
                Осуществляется перестановка строки матрицы A (и столбца B), содержащей главный элемент по столбцу на место текущей рассматриваемой строки (если главный элемент по столбцу не находится в текущей рассматриваемой строке).
                В массив, хранящий порядок переменных в ответе записывается, в какой строке должно быть получено значение переменной текущего рассматриваемого столбца.
                Осуществляется обнуление наддиагональных и поддиагональных элементов текущего рассматриваемого столбца: текущая рассматриваемая строка делится на главный элемент; текущая рассматриваемая строка прибавляется к остальным строкам с таким коэффициентом, чтобы коэффициенты этих строк в текущем рассматриваемом столбце обращались в нули.
            Матрица A получается единичной, а столбец B - содержит решение системы.
            Присваиваем значения элементов столбца B элементам вектора ответов X в соответствии с порядком переменных в ответе. Независимым переменным, которые не определились в процессе решения, присваиваются значения 0.
            Осуществляется подстановка полученного решения в систему. Если система уравнений не обращается в тождества, то функция возвращает значение 1 - решения системы не существует. Иначе функция возвращает 0.
        ------------------------------
        Параметры:
            n: целое число - размерность матрицы A и вектора B
            A: указатель на вещественное число - матрица A
            B: указатель на вещественное число - вектор B
            X: указатель на вещественное число - вектор решения X
            tmp: указатель на вещественное число - дополнительная память
        ------------------------------
        Возвращаемые значения (целое число):
            0: Решение построено
            1: Решения системы не существует

Программа применима для всех видов систем линейных уравнений с квадратной матрицей A, в том числе для недоопределенных систем.

Использованная литература:
    К.Ю. Богачев "Практикум на ЭВМ. Методы решения линейных систем и нахождения собственных значений", Москва, 1998.
    С.П. Куксенко, Т.Р. Газизов "Итерационные методы решения системы линейных алгебраических уравнений с плотной матрицей", Томск, 2007.
    William H. Press, Saul A. Teukolsky, William T. Vetterling, Brian P. Flannery "Numerical Recipes: The Art of Scientific Computing", 2007.

Абдуллаева Евгения, группа М1-17.
