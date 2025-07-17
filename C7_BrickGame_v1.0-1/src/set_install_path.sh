#!/bin/bash

INSTALL_PATH_FILE="install_path.txt"
DEFAULT_BUILD_DIR="builds"

# Функция для запроса пути у пользователя
ask_for_path() {
    read -p "Please enter the installation path (or press Enter to use default: $DEFAULT_BUILD_DIR): " INSTALL_PATH

    if [ -z "$INSTALL_PATH" ]; then
        INSTALL_PATH=$DEFAULT_BUILD_DIR
        echo "Using default path: $INSTALL_PATH"
    fi
}

# Запрашиваем путь у пользователя
ask_for_path

# Проверяем, существует ли директория и доступна ли она для записи
if [ -d "$INSTALL_PATH" ] && [ -w "$INSTALL_PATH" ]; then
    echo "Directory exists and is writable."
elif [ ! -d "$INSTALL_PATH" ]; then
    echo "Directory does not exist. Creating $INSTALL_PATH..."
    mkdir -p "$INSTALL_PATH"
    if [ $? -ne 0 ]; then
        echo "Failed to create directory. Please check permissions."
        exit 1
    fi
else
    echo "Directory is not writable. Please choose a different path."
    exit 1
fi

# Записываем путь в файл install_path.txt
echo "Setting installation path to: $INSTALL_PATH"
echo "$INSTALL_PATH" > "$INSTALL_PATH_FILE"
echo "Installation path set to: $INSTALL_PATH"
