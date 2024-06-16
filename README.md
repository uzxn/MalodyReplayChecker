# MalodyReplayChecker

Malody 回放文件信息查看工具

## 使用方法

### 显示帮助信息

在命令行下执行：`mr` 或 `mr help`。

### 查看回放信息

在命令行下执行：`mr info XXX.mr YYY.mr ...`，其中 `XXX.mr` `YYY.mr` 为回放文件，支持多文件。

例如：`mr info a.mr` `mr info a.mr b.mr c.mr`。

使用例：

```txt
D:\>mr info test.mr
----------------+------------------------------------------------
 File Name      | test.mr
----------------+------------------------------------------------
 Song Name      | Handstream Pack ver.3
 Song Author    | Various Artists
 Difficulty     | [Boss] KisenonP feat. Hatsune Miku - Hayabusa
 Score          | 5354593
 Accuracy       | 98.5972%
 Judgement      | C
 Max Combo      | 1095
 Best           | 2767
 Cool           | 127
 Good           | 5
 Miss           | 6
 Mods           | Const
 Chart md5      | cc4095b3ebeaea3395a1fac3002f13ac
 Time           | 2023-08-10 21:22:34
 Malody Ver     | 4.3.7
----------------+------------------------------------------------
```

### 生成 .csv 文件

> .csv 文件可以直接用 Excel 打开并编辑。

在命令行下执行：`mr csv outfile.csv XXX.mr YYY.mr ...`，其中 `outfile.csv` 为生成文件名，`XXX.mr` `YYY.mr` 为回放文件，支持多文件。

例如：`mr csv out.csv a.mr` `mr csv info.csv a.mr b.mr c.mr`。

使用例：

```txt
D:\>mr csv out.csv test.mr
Current file: test.mr
All finished
```

用 Excel 打开生成的 .csv 文件：

![](excel.png)

### 批量重命名

在文件夹中选中回放文件**直接拖拽**到 `mr.exe` 上（推荐）。

或在命令行下执行：`mr XXX.mr YYY.mr ...`，其中 `XXX.mr` `YYY.mr` 为回放文件，支持多文件。

例如：`mr a.mr` `mr a.mr b.mr c.mr`。

回放文件将会重命名为以下格式：`[游玩时间]_[歌曲名称]_[难度名称]_[判定][ACC].mr`。

例如：`2023-08-10_Handstream Pack ver.3_[Boss] KisenonP feat. Hatsune Miku - Hayabusa_C98.60.mr`。

### 查看新文件名

在命令行下执行：`mr name XXX.mr YYY.mr ...`，其中 `XXX.mr` `YYY.mr` 为回放文件，支持多文件。

例如：`mr name a.mr` `mr name a.mr b.mr c.mr`。

会将 `[游玩时间]_[歌曲名称]_[难度名称]_[判定][ACC].mr` 输出到命令行。

## 编译方法

### Windows

* 使用 Tiny C Compiler
    1. 下载 [Tiny C Compiler](https://bellard.org/tcc/) 并添加到 PATH 目录。
    2. 在仓库根目录下运行 `make.bat`。

* 使用 MinGW（GCC）
    1. 下载安装。
    2. 在仓库根目录下运行 `gmake.bat`。