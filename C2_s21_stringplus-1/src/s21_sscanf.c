#include "s21_string.h"

// Функция для инициализации спецификатора формата
void init_format_specifier(format_specifier *fs) {
  fs->suppress_assign = 0;
  fs->width = -1;
  fs->precision = -1;
  fs->length = 0;
  fs->specifier = '\0';
}

// Пример функций обработки знаковых типов
void handle_int(const char **str, int *out) {
  int sign = 1;
  *out = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }

  *out *= sign;
}

void handle_short_int(const char **str, short int *out) {
  int sign = 1;
  *out = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }

  *out *= sign;
}

void handle_signed_char(const char **str, signed char *out) {
  int sign = 1;
  *out = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }

  *out *= sign;
}

void handle_unsigned_char(const char **str, unsigned char *out) {
  *out = 0;

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }
}

void handle_long_int(const char **str, long int *out) {
  int sign = 1;
  *out = 0;

  while (isspace(**str)) {
    (*str)++;
  }

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }

  *out *= sign;
}

void handle_long_long_int(const char **str, long long int *out) {
  int sign = 1;
  *out = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }

  *out *= sign;
}

// Пример функций обработки беззнаковых типов
void handle_unsigned_int(const char **str, unsigned int *out) {
  *out = 0;

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }
}

void handle_unsigned_short_int(const char **str, unsigned short int *out) {
  *out = 0;

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }
}

void handle_unsigned_long_int(const char **str, unsigned long int *out) {
  *out = 0;

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }
}

void handle_unsigned_long_long_int(const char **str,
                                   unsigned long long int *out) {
  *out = 0;

  while (isdigit(**str)) {
    *out = *out * 10 + (**str - '0');
    (*str)++;
  }
}

// Пример функций обработки других типов
void handle_float(const char **str, double *out) {
  int sign = 1;
  double integer_part = 0.0;
  double fractional_part = 0.0;
  int exponent = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    integer_part = integer_part * 10 + (**str - '0');
    (*str)++;
  }

  if (**str == '.') {
    (*str)++;
    int fractional_divisor = 1;
    while (isdigit(**str)) {
      fractional_part = fractional_part * 10 + (**str - '0');
      fractional_divisor *= 10;
      (*str)++;
    }
    fractional_part /= fractional_divisor;
  }

  if (**str == 'e' || **str == 'E') {
    (*str)++;
    int exponent_sign = 1;
    int exponent_value = 0;
    if (**str == '-') {
      exponent_sign = -1;
      (*str)++;
    } else if (**str == '+') {
      (*str)++;
    }

    while (isdigit(**str)) {
      exponent_value = exponent_value * 10 + (**str - '0');
      (*str)++;
    }

    exponent = exponent_sign * exponent_value;
  }

  *out = sign * (integer_part + fractional_part) * pow(10, exponent);
}

void handle_long_double(const char **str, long double *out) {
  int sign = 1;
  long double integer_part = 0.0;
  long double fractional_part = 0.0;
  int exponent = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    integer_part = integer_part * 10 + (**str - '0');
    (*str)++;
  }

  if (**str == '.') {
    (*str)++;
    long double fractional_divisor = 1;
    while (isdigit(**str)) {
      fractional_part = fractional_part * 10 + (**str - '0');
      fractional_divisor *= 10;
      (*str)++;
    }
    fractional_part /= fractional_divisor;
  }

  if (**str == 'e' || **str == 'E') {
    (*str)++;
    int exponent_sign = 1;
    int exponent_value = 0;
    if (**str == '-') {
      exponent_sign = -1;
      (*str)++;
    } else if (**str == '+') {
      (*str)++;
    }

    while (isdigit(**str)) {
      exponent_value = exponent_value * 10 + (**str - '0');
      (*str)++;
    }

    exponent = exponent_sign * exponent_value;
  }

  *out = sign * (integer_part + fractional_part) * powl(10, exponent);
}

void handle_hex(const char **str, unsigned int *out) {
  *out = 0;

  if (**str == '0' && (*((*str) + 1) == 'x' || *((*str) + 1) == 'X'))
    (*str) += 2;

  while (isxdigit(**str)) {
    if (**str >= '0' && **str <= '9') {
      *out = *out * 16 + (**str - '0');
    } else if (**str >= 'a' && **str <= 'f') {
      *out = *out * 16 + (**str - 'a' + 10);
    } else if (**str >= 'A' && **str <= 'F') {
      *out = *out * 16 + (**str - 'A' + 10);
    }
    (*str)++;
  }
}

void handle_octal(const char **str, unsigned int *out) {
  *out = 0;

  while (**str >= '0' && **str <= '7') {
    *out = *out * 8 + (**str - '0');
    (*str)++;
  }
}

void handle_char(const char **str, char *out) {
  *out = **str;
  (*str)++;
}

void handle_string(const char **str, char *out, int width) {
  int count = 0;
  while (**str && (width == -1 || count < width)) {
    *out++ = *(*str)++;
    count++;
  }
  *out = '\0';
}

void handle_pointer(const char **str, void **out) {
  unsigned long int value = 0;
  while (isspace(**str)) {
    (*str)++;
  }
  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    *str += 2;
  }
  while (isxdigit(**str)) {
    if (**str >= '0' && **str <= '9') {
      value = value * 16 + (**str - '0');
    } else if (**str >= 'a' && **str <= 'f') {
      value = value * 16 + (**str - 'a' + 10);
    } else if (**str >= 'A' && **str <= 'F') {
      value = value * 16 + (**str - 'A' + 10);
    }
    (*str)++;
  }
  *out = (void *)value;
}

// Функции для обработки данных с учетом модификаторов длины

void handle_signed(const char **str, void *out, int length) {
  switch (length) {
    case 1:  // short int
      handle_short_int(str, (short int *)out);
      break;
    case 2:  // long int
      handle_long_int(str, (long int *)out);
      break;
    case 3:  // signed char
      handle_signed_char(str, (signed char *)out);
      break;
    case 4:  // long long int
      handle_long_long_int(str, (long long int *)out);
      break;
    default:  // int
      handle_int(str, (int *)out);
      break;
  }
}

void handle_unsigned(const char **str, void *out, int length) {
  switch (length) {
    case 1:  // unsigned short int
      handle_unsigned_short_int(str, (unsigned short int *)out);
      break;
    case 3:  // unsigned long int
      handle_unsigned_char(str, (unsigned char *)out);
      break;
    case 2:  // unsigned long int
      handle_unsigned_long_int(str, (unsigned long int *)out);
      break;
    case 4:  // unsigned long long int
      handle_unsigned_long_long_int(str, (unsigned long long int *)out);
      break;
    default:  // unsigned int
      handle_unsigned_int(str, (unsigned int *)out);
      break;
  }
}

void handle_float_length(const char **str, void *out, int length) {
  switch (length) {
    case 5:  // long double
      handle_long_double(str, (long double *)out);
      break;
    default:  // double
      handle_float(str, (double *)out);
      break;
  }
}

// Пример функции разбора формата
void parse_format(const char **format, format_specifier *fs) {
  init_format_specifier(fs);
  const char *ptr = *format;

  // Пропускаем пробелы
  while (isspace(*ptr)) ptr++;

  // Проверка на подавление присваивания
  if (*ptr == '*') {
    fs->suppress_assign = 1;
    ptr++;
  }

  // Обработка ширины поля
  if (isdigit(*ptr)) {
    fs->width = 0;
    while (isdigit(*ptr)) {
      fs->width = fs->width * 10 + (*ptr - '0');
      ptr++;
    }
  }

  // Обработка спецификаторов длины
  if (*ptr == 'h' || *ptr == 'l' || *ptr == 'L') {
    if (*ptr == 'h') {
      fs->length = 1;  // Для 'h'
      if (*(ptr + 1) == 'h') {
        fs->length = 3;  // Для 'hh'
        ptr++;
      }
    } else if (*ptr == 'l') {
      fs->length = 2;  // Для 'l'
      if (*(ptr + 1) == 'l') {
        fs->length = 4;  // Для 'll'
        ptr++;
      }
    } else if (*ptr == 'L') {
      fs->length = 5;  // Для 'L'
    }
    ptr++;
  }

  // Обработка спецификатора типа
  if (s21_strchr("cdifsuxXoeEgGpn%", *ptr)) {
    fs->specifier = *ptr;
  }

  // Обновление указателя на текущую позицию в строке формата
  *format = ptr + 1;
}

int s21_sscanf(const char *str, const char *format, ...) {
  if (format == NULL || str == NULL) {
    return -1;
  }
  va_list args;
  va_start(args, format);

  const char *s = str;
  const char *f = format;
  format_specifier fs;

  int matched = 0;
  int chars_read = 0;

  while (*f) {
    if (*f == '%') {
      f++;
      parse_format(&f, &fs);

      if (fs.suppress_assign) {
        while (!isspace(*s)) {
          s++;
          chars_read++;
        }
        f++;
        continue;
      }

      while (isspace(*s)) {
        s++;
        chars_read++;
      }
      if (*s == '\0') fs.specifier = 0;
      switch (fs.specifier) {
        case 'i':
        case 'd':
          handle_signed(&s, va_arg(args, void *), fs.length);
          matched++;
          break;
        case 'u':
          handle_unsigned(&s, va_arg(args, void *), fs.length);
          matched++;
          break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
          handle_float_length(&s, va_arg(args, void *), fs.length);
          matched++;
          break;
        case 'c':
          handle_char(&s, va_arg(args, char *));
          matched++;

          break;
        case 's':
          handle_string(&s, va_arg(args, char *), fs.width);
          matched++;
          break;
        case 'x':
        case 'X':
          handle_hex(&s, va_arg(args, unsigned int *));
          matched++;
          break;
        case 'o':
          handle_octal(&s, va_arg(args, unsigned int *));
          matched++;
          break;
        case 'p':
          handle_pointer(&s, va_arg(args, void **));
          matched++;
          break;
        case 'n':
          *va_arg(args, int *) = chars_read + matched;
          break;
        case '%':
          if (*s == '%') {
            s++;
            chars_read++;
          } else {
            matched = -1;  // Если '%' не совпадает
          }
          break;
        default:
          matched = -1;  // Неизвестный спецификатор
          break;
      }

      // Прерываем цикл, если произошла ошибка
      if (matched == -1) {
        break;
      }

    } else {
      f++;
      chars_read++;
    }
  }

  va_end(args);

  // Если ни один элемент не был распознан, возвращаем -1, как делает sscanf
  if (matched == 0 && *s == '\0') {
    matched = -1;
  }

  return matched;  // Вернуть количество успешно обработанных аргументов
}
