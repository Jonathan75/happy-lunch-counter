# CYDr Simple WIFI Demo
# Tags: Micropython Cheap Yellow Device DIYmall ESP32-2432S028R
# Last Updated: June 15, 2024
# Author(s): James Tobin
# License: MIT
# https://github.com/jtobinart/MicroPython_CYD_ESP32-2432S028R

# from cydr import CYD
#from test import CYD 
import time
import requests


from time import sleep
from ili9341 import Display, color565
from machine import Pin, SPI
from xglcd_font import XglcdFont

spi = SPI(1, baudrate=40000000, sck=Pin(14), mosi=Pin(13))
display_width=240
display_height=320
display = Display(spi, dc=Pin(2), cs=Pin(15), rst=Pin(0), width=display_width, height=display_height)


# Create an instance of CYD with WIFI support
# ssid = "stevens2"    
# password = "6145014403"

ssid = "WPL_Public_Accessll"    
password = ""

# cyd = CYD(wifi_ssid=ssid, wifi_password=password)
# cyd = CYD()
# url = "http://api.coindesk.com/v1/bpi/currentprice.json"
# url = "http://api.open-notify.org/astros.json"
#url = "http://ip-api.com/json/"
url = "https://catfact.ninja/fact"

end_time = 0

# while cyd.wifi_isconnected():
# while True:        
#     x, y = cyd.touches()    # Get recent taps x, y 
# 
#     if time.ticks_ms() > end_time:
#         text = "01234f5678901234f5678901234f56789123456"
#         print(text)
#         cyd.display.draw_text8x8(cyd.display.width // 2, 0, text, cyd.WHITE, background=cyd.BLACK, rotate=90)        
#         end_time = time.ticks_ms() + 180000   # 60000ms = 1 minute
#     if x == 0 and y == 0:
#         continue
# 
#     # Double tap to exit
#     if cyd.double_tap(x,y):
#         cyd.shutdown()




def test():
    """Test code."""
    # Baud rate of 40000000 seems about the max
    spi = SPI(1, baudrate=40000000, sck=Pin(14), mosi=Pin(13))
#     display = Display(spi, dc=Pin(4), cs=Pin(16), rst=Pin(17))
    
#     hspi = SPI(1, baudrate=40000000, sck=Pin(14), mosi=Pin(13))
    display_width=240
    display_height=320
    display = Display(spi, dc=Pin(2), cs=Pin(15), rst=Pin(0), width=display_width, height=display_height,rotation=90)
#     display = Display(spi, dc=Pin(4), cs=Pin(16), rst=Pin(17))


    print('Loading fonts...')
    print('Loading arcadepix')
    arcadepix = XglcdFont('fonts/ArcadePix9x11.c', 9, 11)
    print('arcadepix')
    print('Loading bally')
    bally = XglcdFont('fonts/Bally7x9.c', 7, 9)
    print('Loading broadway')
    broadway = XglcdFont('fonts/Broadway17x15.c', 17, 15)
    print('Loading espresso_dolce')
    espresso_dolce = XglcdFont('fonts/EspressoDolce18x24.c', 18, 24)
    print('Loading fixed_font')
    fixed_font = XglcdFont('fonts/FixedFont5x8.c', 5, 8)
    print('Loading neato')
    neato = XglcdFont('fonts/Neato5x7.c', 5, 7, letter_count=223)
    print('Loading robotron')
    robotron = XglcdFont('fonts/Robotron13x21.c', 13, 21)
    print('Loading unispace')
    unispace = XglcdFont('fonts/Unispace12x24.c', 12, 24)
    print('Loading wendy')
    wendy = XglcdFont('fonts/Wendy7x8.c', 7, 8)
    print('Fonts loaded.')

    display.draw_text(0, 0, 'Arcade Pix 9x11', arcadepix, color565(255, 0, 0), landscape=False)
    display.draw_text(0, 22, 'Bally 7x9',      bally, color565(0, 255, 0), landscape=False)
    display.draw_text(0, 43, 'Broadway 17x15', broadway, color565(0, 0, 255), landscape=False)
    display.draw_text(0, 66, 'Espresso Dolce 18x24', espresso_dolce, color565(0, 255, 255), landscape=False)
    display.draw_text(0, 104, 'Fixed Font 5x8', fixed_font,color565(255, 0, 255), landscape=False)
    display.draw_text(0, 125, 'Neato 5x7',      neato, color565(255, 255, 0), landscape=False)
    display.draw_text(0, 155, 'ROBOTRON 13X21', robotron,color565(255, 255, 255), landscape=False)
    display.draw_text(0, 190, 'Unispace 12x24', unispace,color565(255, 128, 0), landscape=False)
    display.draw_text(0, 220, 'Wendy 7x8', wendy, color565(255, 0, 128), landscape=False)

    sleep(9)
#     display.clear()

#     display.draw_text(0, 255, 'Arcade Pix 9x11', arcadepix,color565(255, 0, 0), landscape=True)
#     display.draw_text(22, 255, 'Bally 7x9', bally, color565(0, 255, 0), landscape=True)
#     display.draw_text(43, 255, 'Broadway 17x15', broadway, color565(0, 0, 255),
#                       landscape=True)
#     display.draw_text(66, 255, 'Espresso Dolce 18x24', espresso_dolce,
#                       color565(0, 255, 255), landscape=True)
#     display.draw_text(104, 255, 'Fixed Font 5x8', fixed_font,
#                       color565(255, 0, 255), landscape=True)
#     display.draw_text(125, 255, 'Neato 5x7', neato, color565(255, 255, 0),
#                       landscape=True)
#     display.draw_text(155, 255, 'ROBOTRON 13X21', robotron,
#                       color565(255, 255, 255),
#                       landscape=True)
#     display.draw_text(190, 255, 'Unispace 12x24', unispace,
#                       color565(255, 128, 0),
#                       landscape=True)
#     display.draw_text(220, 255, 'Wendy 7x8', wendy, color565(255, 0, 128),
#                       landscape=True)
# 
#     sleep(9)
#     display.clear()
# 
#     display.draw_text(0, 0, 'Arcade Pix 9x11', arcadepix, color565(255, 0, 0),
#                       background=color565(0, 255, 255))
#     display.draw_text(0, 22, 'Bally 7x9', bally, color565(0, 255, 0),
#                       background=color565(0, 0, 128))
#     display.draw_text(0, 43, 'Broadway', broadway, color565(0, 0, 255),
#                       background=color565(255, 255, 0))
#     display.draw_text(0, 66, 'Espresso', espresso_dolce,
#                       color565(0, 255, 255), background=color565(255, 0, 0))
#     display.draw_text(0, 104, 'Fixed Font 5x8', fixed_font,
#                       color565(255, 0, 255), background=color565(0, 128, 0))
#     display.draw_text(0, 125, 'Neato 5x7', neato, color565(255, 255, 0),
#                       background=color565(0, 0, 255))
#     display.draw_text(0, 155, 'ROBOTRON 13X21', robotron,
#                       color565(255, 255, 255),
#                       background=color565(128, 128, 128))
#     display.draw_text(0, 190, 'Unispace', unispace, color565(255, 128, 0),
#                       background=color565(0, 128, 255))
#     display.draw_text(0, 220, 'Wendy 7x8', wendy, color565(255, 0, 128),
#                       background=color565(255, 255, 255))
# 
#     sleep(9)
#     display.cleanup()

test()
