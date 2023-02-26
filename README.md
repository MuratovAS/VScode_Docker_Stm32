# VScode и Docker, мощный набор для разработки под Stm32

**Небольшие наблюдения.** Спустя пару лет. 

Данный проект я позиционирую как демонстрацию возможностей. 
Годится ли такая система для постоянного использования?! Скорее нет, чем да.

Некоторые мысли по системам сборки:
- Проект должен открываться в любой IDE, от vim до clion. То есть, не использовать специфические функции IDE. У всех предпочтения разные.
- Структура проекта должна быть простой и понятной, должна быть возможность переиспользовать его фрагменты.
- Как можно меньше надеяться на системные пакеты. (Найдется кто-нибудь кто, будет запускать ее на `alpine linux`, в котором даже `grep` будет работать иначе.)
- Отказаться от `Cmake`. Это становиться головной болью при поддержке проекта. Умелое использование `Makefile` позволяет достичь такого же результата.
- Docker..... Хорошо если он у вас есть :) Пригоден как альтернативный инструмент сборки, но не как основной. (например для сборки на сервере)
- В идеале иметь возможность собирать toolchain из исходного кода автоматически.
- Избегать прегенерации файлов системы сборки.

Несмотря на выше сказанное. Проект спустя пару лет собирается, значит он выполняет свою задачу. 

Советую ознакомиться с еще одним проектом, он более подходит под описание моих критериев. [FPGACode-ide](https://github.com/MuratovAS/FPGACode-ide)

VSCode + Docker (GCC-ARM + CMake + OpenOCD) = IDE

Всех приветствую. В очередной раз речь пойдет о среде разработки под ARM. После многочисленных скитаний по разным IDE и ОС, у меня сформировался некоторый список требований к рабочему пространству. К сожалению, ни одно готовое решение не отвечало всем критерием. В процессе экспериментов, был порожден такой инструмент — набор. У вас возникнет вопрос, а почему мы должны обратить на него внимание?! В качестве аргумента, перечислю список возможностей и преимуществ.

+ Современный и удобный дизайн
+ Изолированность рабочего пространства от системных настроек
+ Скорость развертывания, на новой машине
+ Сохранить возможность генерировать код с помощью **CubeMX**
+ Возможность работы на таких языках как C++ и Rust
+ **Юнит-тестирование**
+ Возможность собирать сложные, иерархические проекты (много контроллерные системы)
+ Возможность установки всевозможных расширений по работе с кодом
    + Cppcheck - статический анализатор кода для языка C/C++ с поддержкой **MISRA C**
    + TODO Highlight - заметки в исходном коде
+ Полноценная работа SWV(**SWO**) в режиме консоли и построение графика
+ Возможность писать скрипты, выполняем на этапе сборки так и в процессе отладки
    + Чиста проекта от “ненужных файлов” созданных CubeMX
    + Система автоматического форматирования кода на этапе сборки проекта на основе AStyle
    + Автогенерируемый файл конфигурации МК (структура памяти, информация о сборке)
+ Интеграция с Git, сборка и тестирование в **GitHub Actions**
+ Open source

Заинтересовало?! Тогда продолжением.

## Как же это все работает

**Docker** - Программное обеспечение для автоматизации развёртывания и управления приложениями в средах с поддержкой контейнеризации. Позволяет «упаковать» приложение со всем его окружением и зависимостями в контейнер, который может быть перенесён на любую Linux-систему, а также предоставляет среду по управлению контейнерами. Если по простому, принцип использования очень похож на виртуальную машину, но при этом таковой не являющейся. Это позволяет избавиться от самого серьезного недостатка, ограничения производительности.

![http://psg.ask-margo.com/fig/container-vs-vm.nersc-shifter-p13.png](Design/README/container-vs-vm.nersc-shifter-p13.png)

**VScode** - редактор исходного кода. Позиционируется как «лёгкий» редактор кода для кроссплатформенной разработки. Имеет **хорошую поддержку** и огромную базу расширений, при этом все Open source. Основные преимущество, это функция **Remote Development**, в других редактора её просто нет. Почитать про нее можно на [оф. сайте](https://code.visualstudio.com/docs/remote/remote-overview), изображение ниже взято именно оттуда. Если в двух словах, у нас есть возможность запустить в docker контейнере часть среды разработки, что позволяет реализовать полноценный Debug. В данной сборке, в контейнере находятся все приложения необходимые для разработки. Ваша ОС остается “чистой”. Так же это **позволяет избежать конфликта версий** и несовместимости различных модулей сборки.

![https://code.visualstudio.com/assets/docs/remote/remote-overview/architecture.png](https://code.visualstudio.com/assets/docs/remote/remote-overview/architecture.png) 

**CMake** - кроссплатформенная система автоматизации сборки программного обеспечения из исходного кода. CMake не занимается непосредственно сборкой, а лишь генерирует файлы управления сборкой из файлов 'CMakeLists.txt'. Благодаря этому приложению мы можем создавать сложные, иерархические проекты и при этом делать это максимально автоматизированно.

Стоит отметить, все происходило на Ubuntu 20.04 c использованием китайского ST-Link2 (модифицированный).

О доработке ST-Link2 можно почитать здесь: https://habr.com/ru/post/402927/

Проекты в этом репозитории **сугубо демонстрационные**, некоторый код в них абсурден.

## Подготовка рабочего пространства

В этот раз нам понадобится совсем не много пакетов…..

Установим непосредственно Visual Studio Code.

~~~bash 
sudo apt install code
~~~

Установим Docker, тут все немного сложнее. Есть детальная [инструкция от разработчика](https://docs.docker.com/engine/install/), а можно выполнить сценарий автоматической установки.

Выставим права для запуска файла, и выполняем его.

```bash
chmod +x ./docker-install-ubuntu.sh  && ./docker-install-ubuntu.sh
```

После этого необходимо, обязательно, **перезагрузить компьютер**. 

Осталось дело за малым, необходимо установить расширение “[Remote Development](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)” в VScode.

## Самое время, интегрировать шаблон проекта

Подключаем **ST-link в usb**, это нужно сделать **ОБЯЗАТЕЛЬНО** до запуска контейнера. Лучше даже до запуска VScode, иначе мы не сможем с ним работать из контейнера. Если вдруг, программатор был отключен во время работы, придется останавливать контейнер, подключать программатор, и заново запустить.

Нажимает на переключатель, в левом нижнем углу.

![image-20200830225059922](Design/README/image-20200830225059922.png)

Нам необходимо открыть WorkSpace в контейнере. Ищем файл в корне проекта с расширением *.code-workspace*, затем открываем его. 

![image-20200830225242471](Design/README/image-20200830225242471.png)

Первое развертывание контейнера занимает продолжительное время, терпеливо ждем. 

Затем, зайдем в меню “Терминал” и выполним задачу “CPU: ST-link info”. Она должна вывести информацию о вашем МК.

**На этом можно считать настройку завершенной.** Можно приступать к работе :)

## Рассмотрим основные элементы интерфейса

Нижнее меню:

![image-20200831103102719](Design/README/image-20200831103102719.png)

1. Кнопка управления соединением с контейнером. Через не можно перемещаться между проектами.
2. Выпадающее меню выбора типа сборки, отладка или релиз. Отличаются уровням оптимизации.
3. Меню выбора ToolChain, здесь мы указываем какой набор компиляторов используем в текущий момент. **Рекомендую оставить значение “ARM”.**
4. Основная кнопка, **запуск сборки** цели
5. Выбор цели сборки, практически всегда можно использовать [all]. С помощью этого пункта можно скомпилировать конкретный подпроект.
6. Самые бесполезные кнопки, у меня так и не вышло заставить их работать с embedded проектом. *В будущем возможно найдется способ починить их.*
7. Выбор цели отладки, такой же бесполезный пункт как и предыдущий. 

Боковая панель:

![image-20200831104850660](Design/README/image-20200831104850660.png)

1. Встроенный **проводник**, с его помощью можно работать непосредственно с файлами
2. В какой то степени, то же проводник, но уже по конкретному проекту. Здесь мы можем отчистить сбоку выбрать цели
3. Менеджер соединений, через него можно управлять контейнерами и их состоянием
4. **Отладка**. Именно через это меню её необходимо запускать, работает в автоматическом режиме через openocd
5. Git менеджер, показывает список изменений с предыдущего коммита
6. Менеджер расширений, с ним познакомились еще в процессе установки IDE

## Немного о структуре проекта

Курсивом выделены автоматически генерируемые файлы.
Жирным выделены файлы и каталоги которые необходимо редактировать.

- .devcontainer - конфигурации Docker
    - devcontainer.json - описывает взаимодействие VScode и Docker, так же здесь описаны расширения необходимые для работы
    - Dockerfile - скрипт, который позволяет автоматизировать процесс построения контейнеров — шаг за шагом, используя при этом base образ
- .vscode - конфигурации IDE
    - cmake-variants.json - описание типов сборки (debug, release)
    - cmake-kits.json - описание toolchain
    - *launch.json - описывает то, как запускать отладку. Генерируется автоматически.*
    - *tasks.json - хранит в себе все пользовательские задачи для IDE. Генерируется автоматически.*

- **A - основной под проект** 
    - **App** - тут хранится код основной прошивки, по совместительству cubemx проект
        - Core - код генерируемый cubemx, в main.c добавлен вызов функций из mainUser.c
        - Drivers - код генерируемый cubemx
        - User - код разработанный пользователем
        - CMakeLists.txt - файл под проекта, ищет исходные коды основных проектов. 
    - **Boot** [опционально] - код кастомного загрузчика, по совместительству cubemx проект.
        Структура аналогична предыдущему пункту.
    - cmake
        - build_info.h.in шаблон файла конфигурации под проекта 
        - BuildInfo.cmake - скрипт генерирующий файлы из шаблона
        - Cleaning.cmake - скрипт чистки “мусора” cubemx
        - **ProjectConfiguration.cmake - все настройки под проекта, разметка памяти МК**
        - **stm32.cmake - настройки MCU использованного в под проекте** 
        - **STM32F334R8Tx_FLASH.ld.in - шаблон для LS**
            Файл **скопирован из cubemx** проекта, модифицирован. Добавляется на конце постфикс *.in*, указывающий что это шаблон. В файле присутствуют переменные *${}* их мы будем определять на моменте сборки.
    - **General** - тут хранится код общий для App и Boot
    - **CMakeLists.txt файл под проекта, ищет исходные коды основных проектов. Тут прописываются  каталоги проекта** 
- **B - основной под проект** 
    Структура аналогична предыдущему пункту. 
- *build - каталог с файлами жизнедеятельности сборки, тут хранятся собранные elf, bin, т.д.*
- cmake - глобальные параметры системы сборки
    - каталог vscode - хранит шаблонов для генерируемых файлов 
    - arm_CompilerSettings.cmake - флаги компилятора
    - GlobalDefines.cmake - макросы компилятора
    - arm_toolchain.cmake - список компиляторов
    - astyle_changes.sh, Astyle.cmake - скрипт запускающий форматирование кода в измененных файлах. 
- **openocd - каталог с cfg, svd для вашего МК**
    - STM32F103xx.cfg - файл для работы с конкретным мк
    - STM32F103xx.svd - файл для просмотра регистров во время отладки
    - ….. 
- Test - Юнит-тестирование.
    **Файлы формата *.cpp автоматически определяются как тесты и компилируются**
    - cmake - каталог с настройками компилятора x86 для запуска тестов
    - Core - каталог с файлами необходимыми для тестов, применимые к всем тестам
    - run.sh - скрипт для запуска всех тестов по очереди.
    - CMakeLists.txt файл под проекта, ищет исходные коды основных проектов. 
        **Примечании: файлы которые нужно тестировать, из основных проектов, должны в конце названия иметь “_”**  
- .astylerc - настройки системы форматирования кода
- CMakeLists.txt - основной файл системы сборки, данный скрипт сканирует все под проекты. 
    Под проектом считается любая папка в которой содержится файл  CMakeLists.txt 
- **WSpace.code-workspace - настройки workspace, настройки всех расширений** 
- .gitignore - список того что не требуется в контроле git системой

Пример проекта расположен в каталоге *firmware*
## Поговорим об отладке

Запуск отладки осуществляется по нажатию данной кнопки, так же тут можно выбрать режим работы swo

![image-20200831000508051](Design/README/image-20200831000508051.png)

Пример работы **SWO Console**, найти её можно во вкладке “Выходные данные”, в разделе SWO…..

![image-20200830221040859](Design/README/image-20200830221040859.png)

Пример работы **SWO Grapher**. Окно вывода графика открывается автоматически.

![image-20200830220636360](Design/README/image-20200830220636360.png)

## Пример лога cmake

~~~bash
[cmake] Sub Projects: A
[cmake] -- Name: EXAMP_01_A
[cmake] -- Memory map:
[cmake]     - Bootloader    [Boot]  size is  0 kb (origin 0x8000000)
[cmake]     - Application   [App]   size is 62 kb (origin 0x8000000)
[cmake]     - Settings              size is  2 kb (origin 0x800f800)
[cmake] -- Used MCU: STM32f334R8T6
[cmake] -- Find Sector: App
[cmake] -- -- Cleaning: ON
[cmake] -- -- AStyle: CHANGES
[cmake] -- IDE: VScode
[cmake] Sub Projects: B
[cmake] -- Name: EXAMP_01_B
[cmake] -- Memory map:
[cmake]     - Bootloader    [Boot]  size is  24 kb (origin 0x8000000)
[cmake]     - Application   [App]   size is 40 kb (origin 0x8006000)
[cmake]     - Settings              size is  0 kb (origin 0x8010000)
[cmake] -- Used MCU: STM32F103C8T6
[cmake] -- Find Sector: App
[cmake] -- -- Cleaning: ON
[cmake] -- -- AStyle: CHANGES
[cmake] -- IDE: VScode
[cmake] Sub Projects: Test
[cmake] -- Test name: UT_pid
[cmake] Status: 
[cmake] -- Configuring done
[cmake] -- Generating done
[cmake] -- Build files have been written to: /workspaces/VScode_Docker_stm32/firmware/build
~~~

## Вопросы, которые могут возникнуть

В: Почему у меня не проверяется “misra c”?
О: Вам необходимо приобрести документ “misra c” и в  Dockerfile, в строке 42, вставить ссылку на скачивание. 

~~~bash
RUN wget -O /opt/CppCheck/addons/misra.txt https://text/text.txt
~~~

Пример оформления документа:

~~~bash
Appendix A Summary of guidelines
Rule 1.1
text text text
Rule 1.2
text text text
......
~~~

В: Почему у меня весь код подчеркнут красным?
О: За это отвечает расширение “C/C++”? по совместительству IntelliSense Он берет информацию из файла *build/compile_commands.json*. После первого запуска этого файла нет. В таком случае необходимо скомпилировать App
и Boot и перезапустить IDE. После этого код в под проекте указанном как рабочий подчеркиваться красным не будет.

В: Почему IDE не видит мой ST-link?
О: Как было сказано выше, ПРОГРАММАТОР нужно подключать ДО запуска контейнера, то есть до запуска IDE

В: Программатор виден в системе, но не доступен из Docker.
О: Одной из причин может быть STM32CubeIDE, который добавляет правило в `/etc/udev/rules.d/` для ST-Link. Починить можно удалением этого файла, или настройкой прав.

```bash
sudo usermod -aG docker $USER
sudo usermod -aG plugdev $USER
sudo udevadm control --reload-rules
```