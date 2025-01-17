# ChatGPT が書いた

# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -O2 -Iinclude

# ディレクトリの定義
SRC_DIR = src
BUILD_DIR = build

# ソースファイルを自動検出
SRCS = $(wildcard $(SRC_DIR)/*.c)

# オブジェクトファイルのパスを生成
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# ターゲットの定義
TARGET = $(BUILD_DIR)/video

# ビルドルール
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# オブジェクトファイル生成ルール
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -rf $(BUILD_DIR)
