# CppSource

Repo for threading homework on 2019/2020 C++ course

# Task 1

Напишите программу, которая будет многопоточно считать сумму элементов в `std::vector`. Протестируйте на 1000 элементах с 10ью потоками: каждый поток должен брать равный диапазон элементов, считать сумму элементов и сохранять эту сумму в общий вектор. Далее поток `main()` должен просуммировать частичные суммы.

# Task 2

Напишите программу, которая будет многопоточно вычислять скалярное произведение двух алгебраических векторов (элементы хранятся `std::vector`) в правом базисе.  Протестируйте на 1000 элементах с 10ью потоками: каждый поток должен брать равный диапазон элементов, считать поэлементно произведение двух векторов и сохранять это произведение в общий вектор. Далее поток `main()` должен взять общий вектор и вычислить сумму его элементов. Вычисление длины должно быть тоже реализовано многопоточно.

# Task 3*

Выполните **Task 2**, создавая 10 потоков только один раз в начале программы. То есть, потоки, которые вычисляли поэлементное произвдение, должны дождаться окончания всех произведений и только потом начинать вычисление сумм. Вам понадобится `notify_all()`.
