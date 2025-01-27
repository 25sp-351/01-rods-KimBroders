Test #1:
    command-line argument (rod length): 47
    input (list of piece prices):
        10, 100
        5, 27
        2, 3
    expected output:
        4 @ 10 = 400
        1 @ 5 = 27
        1 @ 2 = 3
        Remainder: 0
        Value: 430

Test #2:
    command-line argument (rod length): 10
    input (list of piece prices):
        5, 18
        10, 81
        16, 178
    expected output:
        0 @ 5, = 0
        1 @ 10 = 81
        0 @ 16 = 0
        Remainder: 0
        Value: 81

Test #3:
    command-line argument (rod length): 25
    input (list of piece prices):
        3, 10
        4, 14
        5, 17
        18, 184
    expected output:
        1 @ 3 = 10
        1 @ 4 = 14
        0 @ 5 = 0
        1 @ 18 = 184
        Remainder: 0
        Value: 208

Test #4:
    command-line argument (rod length): 43
    input (list of piece prices):
        5, 24
        8, 25
        16, 226
    expected output:
        2 @ 5 = 48
        0 @ 8 = 0
        2 @ 16 = 452
        Remainder: 1
        Value: 500

Test #5:
    command-line argument (rod length): 66
    input (list of piece prices):
        3, 7
        5, 24
        16, 196
    expected output:
        0 @ 3 = 0
        0 @ 5 = 0
        4 @ 16 = 784
        Remainder: 2
        Value: 784

Test #6:
    command-line argument (rod length): 6
    input (list of piece prices):
        10, 73
    expected output:
        0 @ 10 = 0
        Remainder: 6
        Value: 0
        