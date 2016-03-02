# Тестовое задание

Нужно реализовать небольшой Graphics
для рисования графических примитивов на растровом изображении.
Без использования стандартных библиотек типа GDI/GDI+.

## Требования

* Поддержка разных пиксель форматов, для примера достаточно двух,
  желательно из разных colorspace’ов (RGB, CMYK и т. д.).
* Графические примитивы: линия, прямоугольник, эллипс, кривая Безье.
* Рисовать контуры единичной ширины, без заливки.
* Результат сохранять в файл (любой графический формат без потерь).
  GUI делать необязательно, достаточно простой консоли.

Должно получиться что-то такое:

```c++
class Graphics
{
    ...
    void DrawLine(...);
    void DrawRectangle(...);
    void DrawPath(...);
    void DrawEllipse(...);
    void DrawText(string, position);
    ...
};
```

Как бонус можете прикрутить freetype и добавить рисование текста.
Рисовать также только контуры.
Достаточно будет использовать один шрифт с фиксированными настройками.
