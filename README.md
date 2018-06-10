# Blinkenlights

Uses the Fast Fourier Transform to display frequency spectrum on an LED matrix.
It is powered by an Adafruit Feather M0 which has enough processing power to run
the FFT in real time. 3D printed case needs M2.5 standoffs and some low profile
M3 bolts.


![animation](https://lh3.googleusercontent.com/ADkJpR76Y8T1v87dgCgvf0EQ0NSIyNwexFypPOtBqY8uFTy2-gpWoWiywJXV1YDah_V3m_UcYoQEOGWDaPItCThJLzY-HPntpn8f1EyyYxwTv6_5Fz_oO62BfSSUqzPo6G99OGuZpM0r8xi8kyXL9zMTzRqpNsw4o2pwb67yg7FLvTdQb4sxX-TfELsOKxfLYzPO0rLVSj8eGYOpr6PV541MD3T6DfsYGxLuiYI_XwIfp1C69ypxZKV36sbyAZp7JjGBIX0iZCZHBZNT6z0eP2YxYjP7gNpWois4toytyeR8bdYmYsON3znOZzhNa057Tko3F5xCzZe__6QIFINVAeDoZQL7trod9depe28_VgdN7y1C8Uvu6qSZu5WubdPElS7mD3V6H_75_cGKqT8SqMA3CNEpuAgkajfnWLGKGWiW181ep03roPfJOtJHJvC0orbNnvftO3pA6DlyXRGwIFWREOyG-H6ptUU20eM4z6ZHJjNH_kN86VQd3ynSqtNzwqUEN2UgBG-h27vFavBP48ZJ3QbI-RgFgB7uhpaknZ23akLkqJH6aHAN5fS8lQCeQsHrX6JjnTAwXK2c3ws3Cedq-kO10crBWqaraw4W=s290-no)

## BOM

### Electronics

| Part                                   | Adafruit Part No.                                                                              |
|----------------------------------------|------------------------------------------------------------------------------------------------|
| Adafruit Feather M0 Basic              | [2772](https://www.adafruit.com/product/2772)                                                  |
| Adafruit 15x7 CharliePlex LED Matrix   | [3134](https://www.adafruit.com/product/3134)                                                  |
| Adafruit Electret Microphone Amplifier | [1713](https://www.adafruit.com/product/1713) or [1063](https://www.adafruit.com/product/1063) |
| 18650 LiPo Battery                     | [1781](https://www.adafruit.com/product/1781)                                                  |
| Latching Illuminated 16 mm Button      | [1442](https://www.adafruit.com/product/1442)                                                  |

### Hardware

| Item                                                | Qty | McMaster-Carr Part No.                                    |
|-----------------------------------------------------|-----|-----------------------------------------------------------|
| M3 x 6 mm Low-Profile Socket-Head Screw             | 5   | [92855A307](https://www.mcmaster.com/#92855a307/=1d883ft) |
| M3 x 8 mm Low-Profile Socket-Head Screw             | 2   | [92855A309](https://www.mcmaster.com/#92855a309/=1d885do) |
| M3 x 16 mm Low-Profile Socket-Head Screw            | 3   | [92855A316](https://www.mcmaster.com/#92855a316/=1d8861v) |
| M2.5 x 6 mm Nylon Screw                             | 2   | [92492A711](https://www.mcmaster.com/#92492a711/=1d889ul) |
| M2.5 x 8 mm Male-Female Threaded Hex Standoff       | 4   | [95783A054](https://www.mcmaster.com/#95783a054/=1d8882d) |
| M2.5 Nylon Hex Nut                                  | 2   | [93800A350](https://www.mcmaster.com/#93800a350/=1d8896z) |
| Male + Female Machine Pin Header 2.54 mm Pitch 1x12 | 1   | -                                                         |
| Male + Female Machine Pin Header 2.54 mm Pitch 1x16 | 1   | -                                                         |
| Right Angle Pin Header 1x8                          | 1   | -                                                         |
| Right Angle Pin Header 1x5                          | 1   | -                                                         |
| Frosted Acrylic, 2-3 x 26 x 60 mm                   | 1   | -                                                         |

## Assembly

### Wiring

The illuminated toggle power button and microphone can be wired to the bottom of
the Feather's proto board with the right angle header and DuPont connectors.

![fritzing](https://lh3.googleusercontent.com/5NHlh4DSRBiCAwgx9jGlC1z4nyOTzJ-hkCKyq0k9myFz3cnMhCXNBUwAQpkvS9XjRSCH_KKlPkHA11y0URVWCTKKEI75pWN2HY5njxVVwcIKkvesRhXAH0ZrfmAbGbTm1EM5OcFFjkBrW78v1dKi_BxDIysixTqpzAKTVY0HDGx5CnwDk4czp-8PQIG041xC1izkZQSV7WWEAu7jtNe-w4k3jHfUXotvIVkXjRTo58mHtzTbUJU2-jbDhEL83wbA_wAudFv2yeOGmPeVqHMbA3NmQOMYwaifMx8StLzpTHdNddSuFMsTHu6d-PxVNA6Ey-ueueeiqNKJxlW79i-revinEzqWp9w3vFtCr0DEL5aQeePIsh0LMqrx2Xfc4sczWvwlL1zPi4_2M1VnrO4dYrCE7tsA5qs-hc9FFwH-72fK6qKDsVxRDn7HL2eQ7H6uCwaZPYj3rcM9QPsUNtY_I1oIQDr60x_p2R6R_H_Qxh0DE0g9vpHszamnqE90ggl-XAesAUFj2dqL5JlLHx-Yj31qT_xL9xndnLfurvgnVktHMVqI4Ja7bpRaLoEB1c0H9tTOFUSbFpHGPyjTTqh73RkuJsWftzxHwGfS8fV8jMYeytjrHYUZ2Q40keebEb0xEifVMe4kranFMR2ttcaEvy27bJVwMKzSEw=w1222-h634-no)

### 3D Printed Parts

This case was printed at 0.2 mm with supports to prevent chamfered corners from
lifting from the bed. Mic is held into the top with a M3 x 6 mm screw and
washer. The screen holders also use M3 x 6 mm screws. The battery holders use
the two M3 x 8 mm screws, but 6 mm long ones would also work. The Feather is
attached to the bottom with the M2.5 hex standoffs. The two halves are then held
together with the M3 x 18 mm screws.

![the guts](https://lh3.googleusercontent.com/ncu6nhOK2kZerwsVpyn1Z2fhz47v1G1On_dZgy9rqyUxvE5QJxXIVYwNKmy3qEXZMJ6J6Rewye3NP7yaXyfRT97FbaaLzk3Wtd47Z-DKpQmGL6xmrwgOWhgOHlC3PImebf-HS0JxR8d8tWVVO3MRVFcDQbTsIQUaHzMRQlmQh02YkD2qd5oIEyYApS-1d5Fsy9Qzw-YqcRwErJmbQAl-kuV0bNkScedf8TWAZ5nJqm9fWzgCA9ngz-c_xoWuFemX8IKkLvaV8Un9hr7r4mIFRvs_aJi8jsgWj6V8JMneJXGdHKcjU6bc7kj5dNTr8Ytz-5cVEIz4_hmk4BC6_LUvBGt78KZ0GiGNH9FibVq4dPIvAdfE5F2B7qLuhj-hoiXSfZPXhHvm3H0Ea5G24L2F6hDYL2xeAUprYq9PRhDuCJmLdZvtngIxvuYo6XgFTMSdoO6OaP7PmPEr7Ans8xU7lC6X58SSaNU_Qq6LAEpBtuCj-tmO9cBNfiuql_wxSmCzGwM5EjerK0vpKs-JLBU8hjRiS11AJp1EhzFRArywu1Q1LFAPtO3zlLAS-5-nDPRjZS7KX_Vf7EbfRAz70kk3OLs8JghhNuJnPO0CskAicLbgTNz0rdgqbEQneslC8oJtvbtEZC53h4d7XZ8JsL4nGp7Dq2n46NsweQ=w910-h683-no)
