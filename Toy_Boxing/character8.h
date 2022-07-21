#pragma once

unsigned char charPart1P[3][8] = {
	{ 0x7e, 0x81, 0xa5, 0x81, 0xbd, 0x99, 0x81, 0x7e },	/*1P��*/
	{ 0xdf, 0xdf, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff },	/*1P�E��*/
	{ 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff }	/*1P����*/
};

unsigned char charPart2P[3][8] = {
	{ 0x7e, 0xff, 0xdb, 0xff, 0xc3, 0xe7, 0xff, 0x7e },	/*2P��*/
	{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb },	/*2P�E��*/
	{ 0xff, 0xff, 0xff, 0xff, 0xff ,0xdf, 0xdf, 0xdf }	/*2P����*/
};

unsigned char alphabet[27][8] = {
	{ 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00 }, //A
	{ 0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00 }, //B
	{ 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00 },	//C
	{ 0xfc, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xfc, 0x00 },	//D
	{ 0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00 },	//E
	{ 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00 },	//F
	{ 0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3e, 0x00 }, //G
	{ 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc, 0x00 }, //H
	{ 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 }, //I
	{ 0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00 }, //J
	{ 0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0xe6, 0x00 }, //K
	{ 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00 }, //L
	{ 0xc6, 0xee, 0xfe, 0xd6, 0xc6, 0xc6, 0xc6, 0x00 }, //M
	{ 0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00 }, //N
	{ 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00 }, //O
	{ 0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00 }, //P
	{ 0x78, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x1c, 0x00 }, //Q
	{ 0xfc, 0x66, 0x66, 0x7c, 0x78, 0x6c, 0xe6, 0x00 }, //R
	{ 0x78, 0xcc, 0xe0, 0x38, 0x1c, 0xcc, 0x78, 0x00 }, //S
	{ 0xfc, 0xb4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 }, //T
	{ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfc, 0x00 }, //U
	{ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00 }, //V
	{ 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00 }, //W
	{ 0xc6, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0xc6, 0x00 }, //X
	{ 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x78, 0x00 }, //Y
	{ 0xfe, 0xcc, 0x98, 0x30, 0x62, 0xc6, 0xfe, 0x00 }, //Z
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }  //
};