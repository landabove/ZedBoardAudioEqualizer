V1.0.1:

For RX (Line IN and MIC)/ TX (Line out/HPH) configurations, please edit Codec Config Registers/Functions in "adau1761.c"

Select Audio Input Source:
	
	/* Audio Input Path Source Select - MIC/Line IN, L/R Input Volume  */
	
Adau1761_InSelect(pThis, LINE_IN, 0xFF, 0xFF);


Audio Output Source:
Both Line Out and HPH are configured in the Audio Output Path.

Known Issues:
Reset of the zedboard required when switching between MIC/LINE.
Noise appears during MIC initialization.