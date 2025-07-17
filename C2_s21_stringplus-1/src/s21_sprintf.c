#include "s21_string.h"

void init_format_specificator(format_specificator *fs) {
  fs->left_align = 0;
  fs->show_sign = 0;
  fs->space_sign = 0;
  fs->zero_pad = 0;
  fs->width = -1;
  fs->alt_form = 0;
  fs->precision = -1;
  fs->h_modifier = 0;
  fs->l_modifier = 0;
  fs->L_modifier = 0;
}

// Конвертация целого числа в строку
void int_to_string(int value, int base, char *buf) {
  char *ptr = buf, *ptr_start = buf;
  int flag = 0;
  if (value < 0) {
    flag = 1;
    value = -value;
  }

  do {
    *ptr++ = "0123456789abcdef"[value % base];
    value /= base;
  } while (value);
  if (flag) *ptr++ = '-';
  *ptr = '\0';

  // Разворачиваем строку
  ptr--;
  while (ptr_start < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr_start;
    *ptr_start++ = tmp_char;
  }
}

void l_int_to_string(long int value, long int base, char *buf) {
  char *ptr = buf, *ptr_start = buf;
  int flag = 0;
  if (value < 0) {
    flag = 1;
    value = -value;
  }

  do {
    *ptr++ = "0123456789abcdef"[value % base];
    value /= base;
  } while (value);
  if (flag) *ptr++ = '-';
  *ptr = '\0';

  // Разворачиваем строку
  ptr--;
  while (ptr_start < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr_start;
    *ptr_start++ = tmp_char;
  }
}

void ll_int_to_string(long long int value, long long int base, char *buf) {
  char *ptr = buf, *ptr_start = buf;
  int flag = 0;
  if (value < 0) {
    flag = 1;
    value = -value;
  }

  do {
    *ptr++ = "0123456789abcdef"[value % base];
    value /= base;
  } while (value);
  if (flag) *ptr++ = '-';
  *ptr = '\0';

  // Разворачиваем строку
  ptr--;
  while (ptr_start < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr_start;
    *ptr_start++ = tmp_char;
  }
}

void u_int_to_string(unsigned int value, unsigned int base, char *buf) {
  char *ptr = buf, *ptr_start = buf;
  do {
    *ptr++ = "0123456789abcdef"[value % base];
    value /= base;
  } while (value);
  *ptr = '\0';

  // Разворачиваем строку
  ptr--;
  while (ptr_start < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr_start;
    *ptr_start++ = tmp_char;
  }
}

// Lu_Int_To_String
// lu_Int_To_String
void lu_int_to_string(unsigned long int value, unsigned long int base,
                      int uppercase, int alt_form, char *buf) {
  char *ptr = buf, *ptr_start = buf;
  if (alt_form && base != 10) {
    *ptr++ = '0';
    ptr_start++;
    if (base == 16) {
      *ptr++ = uppercase ? 'X' : 'x';
      ptr_start++;
    }
  }

  const char *str_format;
  if (uppercase) {
    str_format = "0123456789ABCDEF";
  } else {
    str_format = "0123456789abcdef";
  }

  do {
    *ptr++ = str_format[value % base];
    value /= base;
  } while (value);
  *ptr = '\0';

  // Разворачиваем строку
  ptr--;
  while (ptr_start < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr_start;
    *ptr_start++ = tmp_char;
  }
}

void llu_int_to_string(unsigned long long int value,
                       unsigned long long int base, char *buf) {
  char *ptr = buf, *ptr_start = buf;

  do {
    *ptr++ = "0123456789abcdef"[value % base];
    value /= base;
  } while (value);
  *ptr = '\0';

  ptr--;
  while (ptr_start < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr_start;
    *ptr_start++ = tmp_char;
  }
}

// Конвертация вещественного числа в строку
void double_to_string(double value, format_specificator fs, char *buf) {
  if (isnan(value)) {
    s21_strncpy(buf, "nan", 4);
    return;
  } else if (isinf(value)) {
    if (value > 0) {
      s21_strncpy(buf, "inf", 4);
    } else {
      s21_strncpy(buf, "-inf", 5);
    }
    return;
  }
  if (fs.precision == -1) {
    fs.precision = 6;
  }
  double temp_value = value, rounding_value = 0.5;
  // Округляем значение до нужного числа знаков
  for (int i = 0; i < fs.precision; i++) {
    rounding_value /= 10;
  }
  // Округляем значение до нужного числа знаков
  if (value < 0) {
    temp_value -= rounding_value;
  } else {
    temp_value += rounding_value;
  }
  int int_part = (int)temp_value;
  int_to_string(int_part, 10, buf);  // Конвертируем целую часть в строку
  s21_size_t index = s21_strlen(buf);
  char *ptr = buf + index;
  if (fs.alt_form) *ptr++ = '.';
  *ptr = '\0';

  if (fs.precision > 0) {
    // Дробная часть числа
    if (temp_value < 0) {
      temp_value = -temp_value;
      int_part = -int_part;
    }
    double fraction = temp_value - int_part;
    // Добавляем десятичную точку и дробную часть
    ptr = buf + index;
    *ptr++ = '.';
    for (int i = 0; i < fs.precision; i++) {
      fraction *= 10;
      int digit = (int)fraction;
      *ptr++ = digit + '0';
      fraction -= digit;
    }
    // Завершаем строку нулевым символом
    *ptr = '\0';
  }
}

void long_double_to_string(long double value, format_specificator fs,
                           char *buf) {
  if (isnan(value)) {
    s21_strncpy(buf, "nan", 4);
    return;
  } else if (isinf(value)) {
    if (value > 0) {
      s21_strncpy(buf, "inf", 4);
    } else {
      s21_strncpy(buf, "-inf", 5);
    }
    return;
  }

  if (fs.precision == -1) fs.precision = 6;

  long double rounding_value = 0.5;
  for (int i = 0; i < fs.precision; i++) {
    rounding_value /= 10;
  }

  if (value < 0) {
    value -= rounding_value;
  } else {
    value += rounding_value;
  }

  long long int_part = (long long)value;

  ll_int_to_string(int_part, 10, buf);

  size_t index = s21_strlen(buf);
  char *ptr = buf + index;
  if (fs.alt_form) *ptr++ = '.';
  *ptr = '\0';

  if (fs.precision > 0) {
    // Дробная часть числа
    if (value < 0) {
      value = -value;
      int_part = -int_part;
    }
    double fraction = value - int_part;
    // Добавляем десятичную точку и дробную часть
    ptr = buf + index;
    *ptr++ = '.';
    for (int i = 0; i < fs.precision; i++) {
      fraction *= 10;
      int digit = (int)fraction;
      *ptr++ = digit + '0';
      fraction -= digit;
    }
    // Завершаем строку нулевым символом
    *ptr = '\0';
  }
}

// Конвертация числа в экспоненциальную форму
void exp_to_string(double value, format_specificator *fs, int uppercase,
                   char *buf, int for_g) {
  if (isnan(value)) {
    s21_strncpy(buf, "nan", 4);
    return;
  } else if (isinf(value)) {
    if (value > 0) {
      s21_strncpy(buf, "inf", 4);
    } else {
      s21_strncpy(buf, "-inf", 5);
    }
    return;
  }

  int exp = 0;
  if (value != 0.0) {
    while (fabs(value) >= 10.0) {
      value /= 10.0;
      exp++;
    }
    while (fabs(value) < 1.0) {
      value *= 10.0;
      exp--;
    }
  }
  if (fs->precision < 0 && !for_g) fs->precision = 6;
  if (fs->precision < 0 && for_g) {
    int len = value < 0 ? -1 : 0;
    char temp_buf[SIZE_NUM];
    int_to_string((int)value, 10, temp_buf);
    len += (int)s21_strlen(temp_buf);
    if (6 - len >= 0) fs->precision = 6 - len;
  }

  double_to_string(value, *fs, buf);
  if (!fs->alt_form) {
    const char *dot = s21_strchr(buf, '.');
    if (dot) {
      char *end = buf + s21_strlen(buf) - 1;
      while (end > dot && *end == '0') {
        *end-- = '\0';
      }
      if (*end == '.') {
        *end = '\0';
      }
    }
  }
  char *ptr = buf + s21_strlen(buf);
  *ptr++ = uppercase ? 'E' : 'e';
  *ptr++ = (exp < 0) ? '-' : '+';
  if (exp < 0) exp = -exp;
  if (exp < 10) *ptr++ = '0';
  int_to_string(exp, 10, ptr);
}

void exp_to_string_long_double(long double value, format_specificator *fs,
                               int uppercase, char *buf, int for_g) {
  if (isnan(value)) {
    s21_strncpy(buf, "nan", 4);
    return;
  } else if (isinf(value)) {
    if (value > 0) {
      s21_strncpy(buf, "inf", 4);
    } else {
      s21_strncpy(buf, "-inf", 5);
    }
    return;
  }
  int exp = 0;
  if (value < 0) value = -value;
  if (value != 0.0) {
    while (value >= 10.0) {
      value /= 10.0;
      exp++;
    }
    while (value < 1.0) {
      value *= 10.0;
      exp--;
    }
  }
  if (fs->precision < 0 && !for_g) fs->precision = 6;
  if (fs->precision < 0 && for_g) {
    int len = value < 0 ? -1 : 0;
    char temp_buf[SIZE_NUM];
    ll_int_to_string((int)value, 10, temp_buf);
    len += (int)s21_strlen(temp_buf);
    if (6 - len >= 0) fs->precision = 6 - len;
  }
  long_double_to_string(value, *fs, buf);
  if (!fs->alt_form) {
    const char *dot = s21_strchr(buf, '.');
    if (dot) {
      char *end = buf + s21_strlen(buf) - 1;
      while (end > dot && *end == '0') {
        *end-- = '\0';
      }
      if (*end == '.') {
        *end = '\0';
      }
    }
  }
  char *ptr = buf + s21_strlen(buf);
  *ptr++ = uppercase ? 'E' : 'e';
  *ptr++ = (exp < 0) ? '-' : '+';
  if (exp < 0) exp = -exp;
  if (exp < 10) *ptr++ = '0';
  ll_int_to_string(exp, 10, ptr);
}

// Конвертация числа в строку с использованием научного или десятичного формата
void g_to_string(double value, format_specificator *fs, int uppercase,
                 char *buf) {
  if (fs->precision < 0) {
    int len = value < 0 ? -1 : 0;
    char temp_buf[SIZE_NUM];
    int_to_string((int)value, 10, temp_buf);
    len += (int)s21_strlen(temp_buf);
    if (6 - len >= 0) fs->precision = 6 - len;
  }

  double abs_value = value < 0 ? -value : value;
  if (abs_value == 0.0 || (abs_value >= 0.0001 && abs_value < 1000000.0)) {
    double_to_string(value, *fs, buf);
    if (!fs->alt_form) {
      const char *dot = s21_strchr(buf, '.');
      if (dot) {
        char *end = buf + s21_strlen(buf) - 1;
        while (end > dot && *end == '0') {
          *end-- = '\0';
        }
        if (*end == '.') {
          *end = '\0';
        }
      }
    }
  } else {
    if (fs->precision > 0) fs->precision--;
    exp_to_string(value, fs, uppercase, buf, 1);
  }
}

void g_to_string_long_double(long double value, format_specificator *fs,
                             int uppercase, char *buf) {
  if (fs->precision < 0) fs->precision = 2;
  if (fs->precision == 0)
    fs->precision = 1;  // В случае, если точность равна 0, устанавливаем её в 1
  long double abs_value = value < 0 ? -value : value;
  if (abs_value == 0.0 || (abs_value >= 0.0001 && abs_value < 1000000.0)) {
    long_double_to_string(value, *fs, buf);
    if (!fs->alt_form) {
      const char *dot = s21_strchr(buf, '.');
      if (dot) {
        char *end = buf + s21_strlen(buf) - 1;
        while (end > dot && *end == '0') {
          *end-- = '\0';
        }
        if (*end == '.') {
          *end = '\0';
        }
      }
    }
  } else {
    if (fs->precision > 0) fs->precision--;
    exp_to_string_long_double(value, fs, uppercase, buf, 1);
  }
}

// Функция для конвертации строки в целое число
int string_to_int(const char *str, char **endptr) {
  int result = 0;

  while (isdigit(*str)) {
    result = result * 10 + (*str - '0');
    str++;
  }
  if (endptr) *endptr = (char *)str;
  return result;
}

int is_stop(char c) {
  const char *stopChars = "diuxXoscpfeEgGn%";
  while (*stopChars) {
    if (c == *stopChars) {
      return 1;
    }
    stopChars++;
  }
  return 0;
}

void parse_format_cpecific(const char *fmt, format_specificator *fs, char **end,
                           va_list args) {
  init_format_specificator(fs);
  const char *p = fmt;
  char *end_ptr;
  // Парсим флаги
  while (*p && !is_stop(*p)) {
    if (*p == '-') fs->left_align = 1;
    if (*p == '+') fs->show_sign = 1;
    if (*p == ' ') fs->space_sign = 1;
    if (*p == '0') fs->zero_pad = 1;
    if (*p == '#') fs->alt_form = 1;
    if (*p == 'h') fs->h_modifier = 1;
    if (*p == 'l') fs->l_modifier++;
    if (*p == 'L') fs->L_modifier = 1;
    if (*p == '*') {
      fs->width = va_arg(args, int);
      if (fs->width < 0) {
        fs->left_align = 1;
        fs->width = -fs->width;
      }
    }
    if (*p == '.') {
      p++;
      if (*p == '*') {
        fs->precision = va_arg(args, int);
        p++;
      } else if (isdigit(*p)) {
        fs->precision = string_to_int(p, &end_ptr);
        p = end_ptr;
      } else {
        fs->precision = 0;
      }
      continue;
    }
    if (isdigit(*p) && *p != '0') {
      fs->width = string_to_int(p, &end_ptr);
      p = end_ptr;
      continue;
    }
    p++;
  }
  *end = (char *)p;
}

void format_number(char **buf_ptr, const char *num_buffer,
                   format_specificator fs) {
  s21_size_t len = s21_strlen(num_buffer);
  // Определяем символ знака
  char sign_char = 0;
  if (num_buffer[0] == '-') {
    sign_char = '-';
    num_buffer++;
    len--;
  } else {
    if (fs.show_sign) {
      sign_char = '+';
    } else if (fs.space_sign) {
      sign_char = ' ';
    }
  }
  // Определяем количество ведущих нулей для точности
  int zero_padding = 0;
  if (fs.precision > (int)len) zero_padding = fs.precision - len;

  // Определяем общую длину числа с ведущими нулями и знаком
  int total_length = len + zero_padding;
  if (sign_char) total_length++;
  // Если нет выравнивания по левому краю и заполнения нулями
  if (fs.width > total_length && !fs.left_align && !fs.zero_pad) {
    s21_memset(*buf_ptr, ' ', fs.width - total_length);
    *buf_ptr += fs.width - total_length;
  }

  // Добавляем символ знака
  if (sign_char) {
    **buf_ptr = sign_char;
    (*buf_ptr)++;
  }

  // Если нет выравнивания по левому краю, но есть заполнение нулями
  if (fs.width > total_length && !fs.left_align && fs.zero_pad) {
    s21_memset(*buf_ptr, '0', fs.width - total_length);
    *buf_ptr += fs.width - total_length;
  }

  // Добавляем нули для дополнения точности
  s21_memset(*buf_ptr, '0', zero_padding);
  *buf_ptr += zero_padding;

  // Копируем число
  s21_strncpy(*buf_ptr, num_buffer, len);
  *buf_ptr += len;

  // Если есть выравнивание по левому краю
  if (fs.left_align && fs.width > total_length) {
    s21_memset(*buf_ptr, ' ', fs.width - total_length);
    *buf_ptr += fs.width - total_length;
  }
}

void process_integer(char **buf, va_list arg, format_specificator fs) {
  char num_buffer[SIZE_NUM];
  if (fs.l_modifier == 1)
    l_int_to_string(va_arg(arg, long int), 10, num_buffer);
  if (fs.l_modifier == 2)
    ll_int_to_string(va_arg(arg, long long int), 10, num_buffer);
  if (fs.l_modifier == 0) int_to_string(va_arg(arg, int), 10, num_buffer);
  format_number(buf, num_buffer, fs);
}

void process_unsigned(char **buf, va_list arg, format_specificator fs,
                      int upper, unsigned int base, int pointer, int mod) {
  char num_buffer[SIZE_NUM];
  if (fs.alt_form || mod) fs.l_modifier = 1;
  if (pointer) {
    fs.l_modifier = 1;
    fs.alt_form = 1;
  }

  if (fs.l_modifier == 1)
    lu_int_to_string(va_arg(arg, unsigned long int), (unsigned long int)base,
                     upper, fs.alt_form, num_buffer);
  if (fs.l_modifier == 2)
    llu_int_to_string(va_arg(arg, unsigned long long int),
                      (unsigned long long int)base, num_buffer);
  if (fs.l_modifier == 0)
    u_int_to_string(va_arg(arg, unsigned int), base, num_buffer);

  format_number(buf, num_buffer, fs);
}

void process_double(char **buf, va_list arg, format_specificator fs) {
  char num_buffer[SIZE_NUM];
  if (fs.L_modifier == 1)
    long_double_to_string(va_arg(arg, long double), fs, num_buffer);
  else
    double_to_string(va_arg(arg, double), fs, num_buffer);
  format_number(buf, num_buffer, fs);
}

void process_exp(char **buf, va_list arg, format_specificator *fs, int upper) {
  char num_buffer[SIZE_NUM];
  if (fs->L_modifier == 1)
    exp_to_string_long_double(va_arg(arg, long double), fs, upper, num_buffer,
                              0);
  else
    exp_to_string(va_arg(arg, double), fs, upper, num_buffer, 0);
  format_number(buf, num_buffer, *fs);
}

void process_g(char **buf, va_list arg, format_specificator *fs, int upper) {
  char num_buffer[SIZE_NUM];
  if (fs->L_modifier == 1)
    g_to_string_long_double(va_arg(arg, long double), fs, upper, num_buffer);
  else
    g_to_string(va_arg(arg, double), fs, upper, num_buffer);
  format_number(buf, num_buffer, *fs);
}

void process_n(int *n, const char *buf, const char *start) {
  if (n) {
    *n = buf - start;
  }
}

void process_string(char **buf, va_list arg, format_specificator fs) {
  const char *string = va_arg(arg, char *);
  int len = s21_strlen(string);
  int width = fs.width;
  int precision = fs.precision;
  if (precision >= 0 && precision < len) {
    len = precision;
  }
  int padding = width > len ? width - len : 0;

  if (!fs.left_align) {
    for (int i = 0; i < padding; i++) {
      **buf = ' ';
      (*buf)++;
    }
  }

  for (int i = 0; i < len; i++) {
    **buf = string[i];
    (*buf)++;
  }

  if (fs.left_align) {
    for (int i = 0; i < padding; i++) {
      **buf = ' ';
      (*buf)++;
    }
  }
}

int s21_sprintf(char *buf, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *buf_ptr = buf;
  char *end_format = s21_NULL;
  format_specificator form_spec;
  while (*format) {
    if (*format == '%') {
      format++;
      init_format_specificator(&form_spec);
      parse_format_cpecific(format, &form_spec, &end_format, args);
      format = end_format;
      switch (*format) {
        case 'd':
        case 'i':
          process_integer(&buf_ptr, args, form_spec);
          break;
        case 'u':
          process_unsigned(&buf_ptr, args, form_spec, 0, 10, 0, 0);
          break;
        case 'x':
        case 'X':
          process_unsigned(&buf_ptr, args, form_spec, *format == 'X', 16, 0, 1);
          break;
        case 'o':
          process_unsigned(&buf_ptr, args, form_spec, 0, 8, 0, 0);
          break;
        case 'f': {
          process_double(&buf_ptr, args, form_spec);
          break;
        }
        case 'e':
        case 'E': {
          process_exp(&buf_ptr, args, &form_spec, *format == 'E');
          break;
        }
        case 'g':
        case 'G': {
          process_g(&buf_ptr, args, &form_spec, *format == 'G');
          break;
        }
        case 'c': {
          const char string[] = {(char)va_arg(args, int), '\0'};
          format_number(&buf_ptr, string, form_spec);
          break;
        }
        case 's': {
          process_string(&buf_ptr, args, form_spec);
          break;
        }
        case 'p':
          process_unsigned(&buf_ptr, args, form_spec, 0, 16, 1, 0);
          break;
        case 'n':
          process_n(va_arg(args, int *), buf_ptr, buf);
          break;
        default:
          format_number(&buf_ptr, "%", form_spec);
          break;
      }
    } else
      *buf_ptr++ = *format;
    format++;
  }
  *buf_ptr = '\0';
  va_end(args);
  return buf_ptr - buf;
}
