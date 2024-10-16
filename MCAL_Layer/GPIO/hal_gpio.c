/* 
 * File:   hal_gpio.h
 * Author: abdo9
 *
 * Created on May 15, 2023, 12:57 PM
 */

#include "hal_gpio.h"

/*Reference to the Data Direction Control Registers*/
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/*Reference to the Data Latch Registers (Read and Write to Data Latch)*/ 
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/*Reference to the Port Status Registers*/
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};


/**
 * @brief initialize the direction of a specific pin @ref direction_t
 * @param _pin_config : Pointer to the pin configurations @ref pin_config_t
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue          
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t* _pin_config){
    Std_ReturnType ret= E_OK;
    
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else{
        switch (_pin_config -> direction){
        case GPIO_DIRECTION_OUTPUT:
            CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
            break;
        case GPIO_DIRECTION_INPUT:
            SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
            break; 
        default: ret = E_NOT_OK;  
        }    
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : Pointer to the pin configurations @ref pin_config_t
 * @param direction_status
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config, direction_t* direction_status){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || direction_status == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }   
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : Pointer to the pin configurations @ref pin_config_t
 * @param logic
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic){
    Std_ReturnType ret= E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else{
        switch (logic){
        case GPIO_LOW:
            CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
            break;
        case GPIO_HIGH:
            SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
            break; 
        default: ret = E_NOT_OK;
        }  
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : Pointer to the pin configurations @ref pin_config_t
 * @param logic
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, logic_t* logic){
    Std_ReturnType ret= E_OK;
    if(_pin_config == NULL || logic == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else {
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }  
    return ret;
}
#endif


/**
 * 
 * @param _pin_config : Pointer to the pin configurations @ref pin_config_t
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t* _pin_config){
    Std_ReturnType ret= E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_direction_initialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : Pointer to the pin configurations @ref pin_config_t
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config){
    Std_ReturnType ret= E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else {
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }  
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize(const port_index_t port, uint8 direction){
    Std_ReturnType ret= E_OK;
    if(port > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }else{
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction_status
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8* direction_status){
    Std_ReturnType ret= E_OK;
    if(direction_status == NULL || port > PORT_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK;
    }else {
        *direction_status = *tris_registers[port];
    }  
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic){
    Std_ReturnType ret= E_OK;
    if(port > PORT_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK;
    }else {
        *lat_registers[port] = logic;
    }  
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8* logic){
    Std_ReturnType ret= E_OK;
    if(logic == NULL || port > PORT_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK;
    }else{
        *logic = *port_registers[port];
    }  
    return ret;
}
#endif

/**
 * 
 * @param port
 * @return status of the function
 *         (E_OK) : The Function finished successfully
 *         (E_NOT_OK) : The Function has an issue
 */
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    Std_ReturnType ret= E_OK;
    if(port > PORT_MAX_NUMBER - 1){
    }else{
        *lat_registers[port] ^= PORT_MASK; 
    }
    return ret;
}
#endif
