# Sandbox


Программа это упрощенную [модель песчаной кучи](https://en.wikipedia.org/wiki/Abelian_sandpile_model), которая позволяет сохранять свои состояния в картинку в [формате BMP](https://en.wikipedia.org/wiki/BMP_file_format).

Изначальное значение передается в файле, путь к которому пользователь передает через CMD

 **-i, --input**    - [tsv-файл](https://en.wikipedia.org/wiki/Tab-separated_values) (tab-separated values) c начальными данными (x коордиата \t y координата \t количество песчинок в точке)

 **-o, --output**   - путь к директории для сохранения картинок(или анимация)

 **-s, --isgif**    - флаг обозначающий, что результатом работу будет анимация с рассыпанием песчаной кучи

Результаты работы программы:

![анимация рассыпания 100000 песчинок](https://github.com/platonoid/Sandbox/blob/3b0d5b2be414043b8f94533214e5ccacf1e00f1f/assets/out.gif) 

![картинка рассыпанных 1000000 песчинок](https://github.com/platonoid/Sandbox/blob/3b0d5b2be414043b8f94533214e5ccacf1e00f1f/assets/file.bmp)
