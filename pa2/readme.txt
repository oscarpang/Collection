CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name: Weiwu Pang

Email Address: Weiwupan@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | (68 , 139, 19 )  |  n/a
Arm                  | (232, 143, 101)  |  138
Vest                 | (30 , 30 , 28 )  |  115
Shirt                | (242, 211, 234)  |  285

================================== Review ===================================
1. Discuss and justify which pixels you chose to compute the average 
background value for method 1. Was there a reason not to choose more or
fewer pixels?

Response 1: The first 51 rows and first 51 columns are my choice to calculate
the average. If choosing too many, the area might overlapping the foreground.
If choosing too few, any abnormal pixel could significantly influence the
average value

2. For method 1, do some experiments to find the range of distance thresholds 
for which the program seems to operate the best. You may use different 
thresholds for the two different sample images (Colbert and Bird). 
Note: threshold values that are too low will cause certain portions of the 
chroma key to stay in the picture; values that are too high will cause parts 
of the foreground image to disappear.

Response 2:
Colbert range: from 70 to 80
Bird range: from 60 to 70

3. For method 2, explain what you implemented and why.  How did you go about 
implementing it? Walk us through a high-level description of what you did in 
your code (and use comments in the actual .cpp file to fill in the details). 
What other alternatives did you consider either before or after you
implemented your selected method?  What are the relative pros and cons of 
these methods? [This question is open-ended!]

Response 3:
By using approach of residual difference to determine the threshold. Firstly
determine the avarage value of each component of chroma key, then calculate
the sum of square of residual difference of each color component of each pixel
comparing with each color component of the average color. Then use the average 
of square of difference to determine the threshold.
================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: 5-6 hrs

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: The expectation of the method2 is unclear that we do not know what level
of generality we should achieve before several summit. I think it would be
better if we could be notified ahead about which set of pictures the program
should be able to processed.

Do you have any other remarks?

:To avoid the failure of the behavior check, I change some place of indention
of the skelaton program. For example the header of the program.
