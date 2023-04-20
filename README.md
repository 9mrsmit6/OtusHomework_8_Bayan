# OtusHomework_8_Bayan
## Options:
 - -h [ --help ]          Помощь
 - -I [ --include ] arg   Список директорий сканирования. По умолчанию ./
 - -E [ --exclude ] arg   Список исключений для сканирования. По умолчанию пустой
 - -r [ --recursive ] arg Просматривать ли поддиректории (рекурсивный режим)
 - -s [ --fsize ] arg     Минимальный размер файла. По умолчанию 1 байт
 - -m [ --mask ] arg      Маска файлов. По умолчанию (\w+).md  (md  файлы). Если маска некорректна то игнорируется
 - -b [ --bsize ] arg     Размер Хеш блока. По умолчанию 10
 - -H [ --hash ] arg      Тип хеш функции [0->CRC32; 1->CRC16; 2->XMODEM]. По умолчанию CRC32
