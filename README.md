# ChenPi11's Blog

有史以来最难以维护的博客

## 使用到的工具

### 包管理器/项目管理器

![NPM](res/npm.png)

- NPM
  - NPM 主要用于管理项目 JavaScript 部分的依赖，同时用于获取一些代码

![CMake](res/cmake.png)

- CMake
  - 用于维护 `mkpostlists` 相关代码，而且提供了一个 configure 脚本

![GNU Autoconf](res/gnu.png)

- GNU Autoconf
  - 用于维护 `build-post` 相关代码

![GNU Make](res/gnu.png)

- GNU Make
  - 这是项目最核心的部分，贯穿于整个构建流程中

![Cargo](res/cargo.png)

- Cargo
  - 用于维护 `new-post` 相关代码

![Python Pip](res/pip.png)

- Python Pip
  - 维护 `build-blog`, `lang-stat` , `trim-wwwroot` 相关代码

![Human](res/human.png)

- 人类
  - 维护项目的所有部分，这是最重要的管理器

### 其他工具

![Debian GNU/Linux](res/debian.png)

- 类 Unix 系统
  - 如果想要开发，必须使用类 Unix 系统，优先选择 Debian GNU/Linux

![Git](res/git.png)

- Git
  - 使用 Git 进行版本控制

![GitHub](res/github.png)

- GitHub
  - 使用 GitHub 托管项目和静态网页

![VS Code](res/vscode.png)

- VS Code
  - IDE

![Copilot](res/copilot.png)

- Copilot
  - 用于辅助开发，其重要性仅次于人类

![MarsCode](res/marscode.png)

- MarsCode
  - 用于代码补全，其重要性仅次于 Copilot

![WSL](res/wsl.png)

- WSL
  - 提供运行环境

![Microsoft Windows](res/windows.png)

- Microsoft Windows
  - 提供 WSL 和 VSCode 的运行环境

![Lenovo Laptop](res/lenovo.png)

- Lenovo 笔记本
  - 提供 Microsoft Windows 的运行环境

![Logitech Mouse](res/logitech.png)

- Logitech 鼠标
  - 使得开发更加流畅

## 使用到的语言

![HTML](res/html5.png)

- HTML
  - 用于显示网页

![CSS](res/css3.png)

- CSS
  - 用于美化网页

![JavaScript](res/javascript.png)

- JavaScript
  - 用于添加交互和动画

![Shell Script](res/bash.png)

- Shell Script
  - 用于自动化构建和部署

![Makefile](res/gnu.png)

- Makefile
  - 管理构建流程

![Python](res/python.png)

- Python
  - 用于编写脚本和工具

![Rust](res/rust.png)

- Rust
  - 用于编写脚本和工具

![C](res/c.png)

- C
  - 用于编写脚本和工具

![C++](res/cpp.png)

- C++
  - 用于编写脚本和工具

![TypeScript](res/typescript.png)

- TypeScript
  - 用于编写脚本和工具

![Markdown](res/markdown.png)

- Markdown
  - 用于编写文档，文章和文章

![M4](res/gnu.png)

- M4
  - 用于编写 Autoconf 脚本

![YAML](res/yaml.png)

- YAML
  - 用于配置 Rubisco 工作流，GitHub Actions 等

![TOML](res/toml.png)

- TOML
  - 用于配置 Rust 项目

![JSON](res/json.png)

- JSON
  - 用于配置 NPM 项目，TypeScript 项目，Rubisco 项目等

## 依赖项

- 一个 POSIX Shell 和 类 Unix 环境
  - 必须
  - 推荐使用 Debian GNU/Linux
  - 推荐使用 Bash 和 Zsh

- Coreutils
  - 必须
  - 需要 `arch`, `uname`, `basename`, `cat`, `chmod`, `cp`, `cut`, `date`,
    `dirname`, `echo`, `expr`, `free`, `head`, `hostname`, `install`, `ln`,
    `ls`, `mkdir`, `mktemp`, `mv`, `od`, `rm`, `rmdir`, `sleep`, `sort`, `tail`,
    `touch`, `tr`, `true`, `uname`, `wc`

- GNU Awk
  - 必须

- 本地 C 和 C++ 编译器，链接器
  - 必须
  - 推荐使用 GCC

- Git
  - 必须

- Gnulib
  - 必须
  - 必须能够提供 gnulib-tool 命令，参见 <http://www.gnu.org/software/gnulib/>

- GNU Autoconf, GNU Automake, GNU M4
  - 必须

- GNU sed
  - 必须

- Grep
  - 必须

- GNU Make
  - 必须

- Cargo, rustc
  - 必须

- CMake
  - 必须

- Go
  - 必须

- Node.js, npm
  - 必须

- Python, python3-pip, python3-venv
  - 必须

- Screenfetch
  - 必须

- GNU Gettext
  - 必须

- bsdutils
  - 必须，需要 `script` 命令

## 部署

### 安装依赖

**注意：Debian 原版的 Node.js 版本过低，需要手动换源安装新版本！**

```shell
sudo apt update
sudo apt install -y coreutils gnulib autoconf automake m4 sed grep make cmake golang nodejs npm python3-pip python3-venv screenfetch gettext bsdutils
```

### 安装 Cargo, rustc

尽管 Debian 官方源已经提供了 Cargo，但是版本过低，需要手动安装新版本。

Debian sid 提供了 rustup 用于安装 Rust 工具链，但是有些 Debian 稳定版并未提供 rustup，需要手动安装。

```shell
sudo apt update
sudo apt install rustup
rustup install stable
rustup default stable
```

### 安装 cargo-make

**注意：确保你的 `~/.cargo/bin` 在 `PATH` 中！**

不同的发行版安装 `cargo-make` 的方式可能不同，参考 `cargo-make` 仓库中对于安装的描述。

这是我使用的安装方式：

```shell
cargo install --force cargo-make
```

### 换源

由于官方源访问速度慢，或者是版本过低，需要换源。

#### Nodesource 源：提供新版本的 Node.js

```shell
curl -fsSL https://deb.nodesource.com/setup_23.x | sudo bash -
```

#### Rustup 源：提供 Rustup 工具链

```shell
export RUSTUP_DIST_SERVER=https://mirrors.tuna.tsinghua.edu.cn/rustup
rustup install stable
rustup default stable
```

#### Cargo 源：提供 Crate.io 上的 Rust 包

首先创建 `~/.cargo/config.toml` 文件

```shell
mkdir -p ~/.cargo
touch ~/.cargo/config.toml
```

然后编辑 `~/.cargo/config.toml` 文件，添加以下内容

> 注意：这会更改用户全局的 Cargo 源

```toml
[source.crates-io]
replace-with = 'tuna'

[source.tuna]
registry = "https://mirrors.tuna.tsinghua.edu.cn/git/crates.io-index.git"
```

#### NPM 源：提供 NPM 包

> 注意：这会更改用户全局的 NPM 源

```shell
sudo npm install -g nrm
sudo nrm ls # 列出所有可用源
#  npm ---------- https://registry.npmjs.org/
#  yarn --------- https://registry.yarnpkg.com/
#* tencent ------ https://mirrors.cloud.tencent.com/npm/
#  cnpm --------- https://r.cnpmjs.org/
#  taobao ------- https://registry.npmmirror.com/
#  npmMirror ---- https://skimdb.npmjs.com/registry/
#  huawei ------- https://repo.huaweicloud.com/repository/npm/
nrm use tencent # 使用腾讯源
```

#### Pip 源：提供 Python 包

> 注意：这会更改用户全局的 Pip 源

```shell
pip config set global.index-url https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple
```

### 克隆仓库

```shell
git clone https://github.com/ChenPi11/ChenPi11.github.io --depth 1
```

### 安装 Go 依赖

```shell
go mod tidy
```

### 构建

```shell
cd ChenPi11.github.io
./scripts/build.sh
```

### 运行

```shell
make run
```
