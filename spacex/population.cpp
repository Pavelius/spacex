#include "main.h"

BSDATA(populationi) = {
	{"NoPopulated", "????????????", "?? ????????? ?????? ??????? ????????? ????????????. ??????? ?? ??????????."},
	{"Outposts", "?????", "?? ??????? ???????????? ???????? ????? ??????????? ??? ??????????????. ?????????? ????????? ???????????."},
	{"Colonies", "???????", "?? ??????? ????????? ????????? ????????? ???????. ????????? ?????????? ??????????????????."},
	{"Cities", "??????", "?? ??????? ???????????? ??????? ?????? ? ??? ???????? ???????? ???????? ??????????."},
	{"Overpopulated", "????????????", "??? ??????????? ??????? ???????? ???????? ???????. ??????????? ??????-??????????, ????????????, ??????? ?????????."},
};
assert_enum(populationi, Overpopulated)