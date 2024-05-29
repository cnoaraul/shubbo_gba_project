#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_ptr.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_item.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_first_attributes.h"
#include "bn_sprite_third_attributes.h"
#include "bn_sprite_position_hbe_ptr.h"
#include "bn_sprite_first_attributes_hbe_ptr.h"
#include "bn_sprite_third_attributes_hbe_ptr.h"
#include "bn_sprite_affine_second_attributes.h"
#include "bn_sprite_regular_second_attributes.h"
#include "bn_sprite_affine_second_attributes_hbe_ptr.h"
#include "bn_sprite_regular_second_attributes_hbe_ptr.h"


#include "common_fixed_8x8_sprite_font.h" // common es una constante al q pertenece el resource
#include "common_new_8x8_sprite_font.h" // common es una constante al q pertenece el resource
#include "bn_sprite_items_font_8x8_palette_black.h"
#include "bn_sprite_items_font_8x8_palette_yellow.h"
#include "common_info.h"

#include "bn_regular_bg_items_company_logo.h"
#include "bn_regular_bg_items_main_stage_bg.h" // "bn_sprite_items" convierte bmp en .h y permite su uso

#include "bn_sprite_items_shubbo_design.h"

// UI
#include "bn_sprite_items_btn_food.h"
#include "bn_sprite_items_btn_emotion.h"
#include "bn_sprite_items_btn_emotion_press.h"
#include "bn_sprite_items_btn_food_press.h"
#include "bn_sprite_items_btn_medicine.h"
#include "bn_sprite_items_btn_medicine_press.h"
#include "bn_sprite_items_emotion_indicator.h"
#include "bn_sprite_items_hunger_indicator.h"
#include "bn_sprite_items_health_indicator.h"


namespace {

    void show_splash(){

    bn::bg_palettes::set_transparent_color(bn::color(31, 0, 0));
    bn::regular_bg_ptr cnrl_logo = bn::regular_bg_items::company_logo.create_bg(0, 0);
    
        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void gameplay(){

        // La paleta se restaura
        bn::bg_palettes::set_transparent_color(bn::color(15, 15, 15));
        // Se crean las fuentes
        // Fuentesde texto
        bn::sprite_text_generator small_variable_text_generator(common::new_8x8_sprite_font);
        small_variable_text_generator.set_center_alignment();
        // Fuentes de titutlo
        bn::sprite_text_generator big_fixed_text_generator(common::fixed_8x8_sprite_font);
        big_fixed_text_generator.set_center_alignment();
        
        bn::vector<bn::sprite_ptr, 32> text_sprites;
        big_fixed_text_generator.set_palette_item(bn::sprite_items::font_8x8_palette_yellow.palette_item());
        
        // CREANDO ESCENA PRINCIPAL
        bn::regular_bg_ptr main_stage_bg = bn::regular_bg_items::main_stage_bg.create_bg(0, 0);
        bn::sprite_ptr shubbo_sprite = bn::sprite_items::shubbo_design.create_sprite(0, 0);
    
        //small_variable_text_generator.set_palette_item(bn::sprite_items::font_8x8_palette_black.palette_item());

        // AÑADIENDO UI
        bn::sprite_ptr btn_emotion_indicator = bn::sprite_items::emotion_indicator.create_sprite(-95, -63);
        bn::sprite_ptr btn_hunger_indicator = bn::sprite_items::hunger_indicator.create_sprite(-45, -63);
        bn::sprite_ptr btn_health_indicator = bn::sprite_items::health_indicator.create_sprite(5, -63);
        small_variable_text_generator.generate(-72,-63, "100", text_sprites);
        small_variable_text_generator.generate(-22,-63, "100", text_sprites);
        small_variable_text_generator.generate(28,-63, "100", text_sprites);
        bn::sprite_ptr btn_emotion_press_sprite = bn::sprite_items::btn_emotion_press.create_sprite(-95, 60);
        bn::sprite_ptr btn_emotion_sprite = bn::sprite_items::btn_emotion.create_sprite(-95, 60);
        bn::sprite_ptr btn_food_press_sprite = bn::sprite_items::btn_food_press.create_sprite(-56, 60);
        bn::sprite_ptr btn_food_sprite = bn::sprite_items::btn_food.create_sprite(-56, 60);
        bn::sprite_ptr btn_medicine_press_sprite = bn::sprite_items::btn_medicine_press.create_sprite(-20, 60);
        bn::sprite_ptr btn_medicine_sprite = bn::sprite_items::btn_medicine.create_sprite(-20, 60);
        
        


        while(true)          //(! bn::keypad::start_pressed())
        {
        bn::core::update();

        // CAPTURA LAS INPUT
        if(bn::keypad::up_pressed()) //PRESIONA EL BOTON COMIDA
        {
            btn_food_sprite.set_visible(false);
            btn_food_press_sprite.set_visible(true);
        } 
        else if(bn::keypad::up_released())
        {
            btn_food_press_sprite.set_visible(false);
            btn_food_sprite.set_visible(true);
        }

        if(bn::keypad::left_pressed()) //PRESIONA EL BOTON AFECTO
        {
            btn_emotion_sprite.set_visible(false);
            btn_emotion_press_sprite.set_visible(true);
        } 
        else if(bn::keypad::left_released())
        {
            btn_emotion_sprite.set_visible(true);
            btn_emotion_press_sprite.set_visible(false);
        }
        if(bn::keypad::right_pressed()) //PRESIONA EL BOTON INJECCION
        {
            btn_medicine_sprite.set_visible(false);
            btn_medicine_press_sprite.set_visible(true);
        } 
        else if(bn::keypad::right_released())
        {
            btn_medicine_sprite.set_visible(true);
            btn_medicine_press_sprite.set_visible(false);
        }

        }

    }

    /*void input(bn::keypad::key_type key, bn::sprite_ptr& sprite)
    {
        bn::sprite_palette_ptr sprite_palette = sprite.palette();

        if(bn::keypad::pressed(key))
        {
            sprite_palette.set_fade(bn::colors::red, 0.5);
        }
        else if(bn::keypad::released(key))
        {
            sprite_palette.set_fade(bn::colors::orange, 0.5);
        }
        else if(bn::keypad::held(key))
        {
            sprite_palette.set_fade(bn::colors::yellow, 0.5);
        }
        else
        {
            sprite_palette.set_fade_intensity(0);
        }
    }
    */

}

int main()
{
    bn::core::init();

    bn::bg_palettes::set_transparent_color(bn::color(18, 18, 18));

    
    while(true)
    {
        bn::core::update();
        show_splash();
        bn::core::update();
        gameplay();
        bn::core::update();

    }


}
