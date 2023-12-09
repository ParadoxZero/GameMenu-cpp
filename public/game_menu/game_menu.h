/*
    Copyright (c) 2023 Sidhin S Thomas. All rights reserved
*/

#include <_types/_uint32_t.h>
#include <functional>
#include <string>

namespace game_menu {

    typedef uint8_t Color;

    enum Align {
        Left = 0,
        Center = 1,
        Right = 2
    };

    struct MenuItem {
        std::function<bool()> action;
        std::string title;
    };

    struct ColorScheme {
        Color TitleColor;
        Color ItemColor;
        Color SelectedColor;
    };

    struct Padding {
        int top;
        int left;
        int bottom;
        int right;
    };

    template<typename FontType>
    struct Style {
        FontType &TitleFont;
        FontType &ItemFont;

        uint32_t TitleFontSize;
        uint32_t ItemFontSize;

        float MenuTitleScaleFactor;
        float MenuItemScaleFactor;

        ColorScheme ColorScheme;

        Padding PaddingTitle;
        Padding PaddingItems;

        Align TitleAlign;
        Align ItemAlign;
    
    };



} // namespace game_menu