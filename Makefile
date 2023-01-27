# 定義済みマクロの再定義
CC            = gcc 
CFLAGS        = -O2 -g -Wall -Wno-unused-result
LIBS          = -lm
OBJS1         = myfopen.o crane_3dmodel.o neural_network.o bat_algorithm.o crane_control.o crane-ba01.o
PROGRAM1      = crane-ba01
OBJS2         = myfopen.o crane_3dmodel.o neural_network.o crane_control_data.o crane-res01.o
PROGRAM2      = crane-res01

.PHONY: all
all:	$(PROGRAM1) $(PROGRAM2)

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .o

# プライマリターゲット
$(PROGRAM1): $(OBJS1)
	$(CC) -o $(PROGRAM1) $^ $(LIBS)
$(PROGRAM2): $(OBJS2)
	$(CC) -o $(PROGRAM2) $^ $(LIBS)

# サフィックスルール
.c.o:
	$(CC) $(CFLAGS) -c $<

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(PROGRAM1) $(PROGRAM2) $(OBJS1) $(OBJS2) *.dat

# ヘッダファイルの依存関係
crane_3dmodel.o: crane.h
neural_network.o: nn.h
bat_algorithm.o:crane.h nn.h bat.h
crane_control.o:nn.h crane.h
crane_control_data.o:nn.h crane.h
crane-ba01.o: crane.h nn.h bat.h
crane-res01.o: crane.h nn.h
