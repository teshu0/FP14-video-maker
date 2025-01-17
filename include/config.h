// 動画の設定を管理する構造体と関数の定義

struct Config
{
    // video size
    unsigned int width;
    unsigned int height;

    // frames
    unsigned int frames;
};

// config functions
struct Config load_config(const char *path);
void save_config(const char *path, struct Config *config);
