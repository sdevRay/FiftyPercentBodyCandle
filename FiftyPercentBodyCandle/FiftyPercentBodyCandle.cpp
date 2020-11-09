//---------------------------------------------------------------------------
// <50% Body Candle indicator
// Ray Hancock 2020
//---------------------------------------------------------------------------

#include <windows.h>
#include "IndicatorInterfaceUnit.h"
#include "TechnicalFunctions.h"

//// External variables
bool EnableIndicator;

//// Buffers
TIndexBuffer FiftyPercent1, FiftyPercent2, FiftyPercent3, FiftyPercent4;

//---------------------------------------------------------------------------
// Initialize indicator
//---------------------------------------------------------------------------
EXPORT void __stdcall Init()
{
	// define properties
	IndicatorShortName("<50% Body Candle");
	SetOutputWindow(ow_ChartWindow);
	SetEmptyValue(-1);

	FiftyPercent1 = CreateIndexBuffer();
	FiftyPercent2 = CreateIndexBuffer();
	FiftyPercent3 = CreateIndexBuffer();
	FiftyPercent4 = CreateIndexBuffer();

	IndicatorBuffers(4);

	RegOption("Enable", ot_Boolean, &EnableIndicator);
	EnableIndicator = true;

	SetIndexBuffer(0, FiftyPercent1);
	SetIndexStyle(0, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(0, "Up wick");

	SetIndexBuffer(1, FiftyPercent2);
	SetIndexStyle(1, ds_None, psSolid, 1, clOrange);
	SetIndexLabel(1, "Up filler");

	SetIndexBuffer(2, FiftyPercent3);
	SetIndexStyle(2, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(2, "Down wick");

	SetIndexBuffer(3, FiftyPercent4);
	SetIndexStyle(3, ds_ColoredCandles, psSolid, 1, clOrange);
	SetIndexLabel(3, "Down filler");
}

EXPORT void __stdcall OnParamsChange()
{
}

//---------------------------------------------------------------------------
// Calculate requested bar
//---------------------------------------------------------------------------
EXPORT void __stdcall Calculate(int index)
{
	double high, low, open, close, half, hlHalf, candle;
	int emptyValue = -1;

	open = Open(index);
	close = Close(index);
	high = High(index);
	low = Low(index);
	half = 0.5;

	hlHalf = abs(high - low) * half;
	candle = abs(open - close);

	if (hlHalf > candle && EnableIndicator)
	{
		FiftyPercent1[index] = open;
		FiftyPercent2[index] = high;
		FiftyPercent3[index] = low;
		FiftyPercent4[index] = close;
	}
	else
	{
		FiftyPercent1[index] = emptyValue;
		FiftyPercent2[index] = emptyValue;
		FiftyPercent3[index] = emptyValue;
		FiftyPercent4[index] = emptyValue;
	}
}