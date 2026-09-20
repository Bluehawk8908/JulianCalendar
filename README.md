# Julian Calendar Converter
A small windows application that allows the user to enter dates and convert them from Old Style to New Style or vice versa, as necessary when reading certain documents from the 18th and 19th century, or working with the liturgical calendar of the Orthodox Christian churches.  

This entails adding or subtracting a [certain number of days, which varies from century to century](https://en.wikipedia.org/wiki/Gregorian_calendar#Difference_between_Gregorian_and_Julian_calendar_dates), and incrementing the month and year if necessary. A button to fetch today's date is also provided for convenience. The custom icon included is of the [Cyrillic letter Yat](https://en.wikipedia.org/wiki/Yat), which was removed from Russian typography in 1918 around the same time as the Soviet Union adopted the Gregorian calendar reforms to align itself with the rest of the modern world, but is retained in Church Slavonic, so the letter may be emblematic of the old Empire and its calendar.
<p align="center">
  <img src="https://i.imgur.com/cffDg4s.png" />
</p>  

This was written mostly as an exercise to use the Win32 API in C++ to write an old school windows app "from scratch". No particular effort was paid to aesthetics and if the program is minimized, it starts misbehaving. I don't plan on fixing it and is offered here as-is. If I revisit the idea, it will probably be built in WinForms. 
