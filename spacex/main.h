#include "answers.h"
#include "crt.h"
#include "dataset.h"
#include "point.h"
#include "stringbuilder.h"

#pragma once

enum variant_s : unsigned char {
	NoVariant,
	Location, Planet, Size, Ship, Squad, System,
};
enum resource_s : unsigned char {
	Credits, Ore, Food, Medical, Drugs,
};
enum stat_s : unsigned char {
	Gunner, Pilot, Technic, Leader,
	Jump, Speed, Power, Armor, Vision, Hull,
	Jail, Medlab, Techlab, Stock, Barracs,
	Crew,
	HullDamage,
};
enum sduad_s : unsigned char {
	Civilians, Scientists, Technics,
	Militia, Soldiers, HeavySoldiers, EliteSoldiers,
};
enum population_s : unsigned char {
	NoPopulated, Outposts, Colonies, Cities, Overpopulated,
};
enum landscape_s : unsigned char {
	AsteroidFields,
	TerrainRealm, ColdRealm, SandRealm, WaterRealm, FoggyJungles, RockyRealm, CorrosiveHell,
};
enum size_s : unsigned char {
	Diminutive, Small, Medium, Large, Huge, Gigantic,
};
enum fraction_s : unsigned char {
	Independed, Player, Confideration, Rebels, Corporation, Pirates,
};
enum building_s : unsigned char {
	Administration, Hangar, Marketplace, Spacedocks, Wilderness,
};
enum location_s : unsigned char {
	Plains, Mountains, Desert, Forest, Swamp,
	TinyOutpost, SmallColony, MediumCity, LargeCity, HugeCity, Megapolis,
};
enum gender_s : unsigned char {
	Male, Female,
};
enum result_s : unsigned char {
	Fail, PartialSuccess, Success, CriticalSuccess,
};
typedef cflags<building_s> buildingf;
typedef cflags<fraction_s> fractionf;
struct statable : dataset<stat_s, HullDamage, unsigned short> {};
struct resourceable : dataset<resource_s, Drugs, int> {};
struct varianti {
	const char*			id;
	array*				source;
	unsigned			names[2];
};
class variant {
	union {
		unsigned char	c[4];
		unsigned		u;
	};
public:
	constexpr variant() : u(0) {}
	constexpr variant(unsigned char t, unsigned char n) : c{n, 0, 0, t} {}
	constexpr variant(unsigned u) : u(u) {}
	variant(const char* v);
	variant(const void* v);
	constexpr operator int() const { return u; }
	constexpr explicit operator bool() const { return u != 0; }
	template<class T> operator T*() const { return (T*)((T::kind == c[3]) ? getpointer() : 0); }
	void				act(const char* format, ...) const;
	void				actv(stringbuilder& sb, const char* format, const char* format_param) const;
	gender_s			getgender() const;
	void*				getpointer() const { return bsdata<varianti>::elements[c[3]].source->ptr(u & 0xFFFFFF); }
	constexpr variant_s	getkind() const { return (variant_s)c[3]; }
	const char*			getname() const;
};
struct varianta {
	short unsigned		start;
	short unsigned		count;
	const variant*		begin() const { return bsdata<variant>::elements + start; }
	const variant*		end() const { return begin() + count; }
};
class object : public variant {
	char				status[4];
public:
	int					getcount() const { return status[0]; }
	int					getweight() const;
};
class taski {
	char				counter;
public:
	constexpr taski() : counter(0) {}
	void				addcounter(int v) { counter += v; }
	int					getcounter() const { return counter; }
	void				setcounter(int v) { counter = v; }
};
class settlementi : public taski {
	const char*			id;
	const char*			name;
	size_s				size;
	fraction_s			fraction;
	buildingf			buildings;
public:
	bool				is(building_s v) const { return buildings.is(v); }
	void				play();
	void				rest();
	void				visit_goverment();
	void				remove(building_s v) { buildings.remove(v); }
	void				set(building_s v) { buildings.add(v); }
};
struct damagei {
	unsigned char		hits[2];
	unsigned char		count;
	unsigned char		range;
	int					roll(int chance_critical = 0) const;
};
struct locationi {
	const char*			id;
	const char*			name;
};
struct landscapei {
	const char*			id;
	const char*			name;
};
struct sizei {
	const char*			id;
	const char*			name;
};
struct populationi {
	const char*			id;
	const char*			name;
};
struct planeti {
	static const variant_s kind = Planet;
	const char*			id;
	const char*			name;
	fraction_s			fraction;
	point				position;
	variant				parent;
	population_s		population;
	landscape_s			landscape;
	size_s				size;
	void				paint() const;
};
struct systemi {
	static const variant_s kind = System;
	const char*			id;
	const char*			name;
	void				play();
	void				paint() const;
	void				prepare();
};
struct variants : adat<variant, 128> {
	void				addships(const systemi* fs, point fp, int r);
	void				addplanets(const systemi* fs);
};
struct objectable : adat<object, 32> {
};
struct shipi : statable {
	static const variant_s kind = Ship;
	variant				parent;
	point				position;
	size_s				size;
	variant				location;
	objectable			objects;
};
struct squadi {
	const char*			id;
	const char*			name;
};
struct troopi : public variant {
	char				count;
	char				killed;
	char				wounded;
};
struct fractioni {
	const char*			id;
	const char*			name;
	fractionf			friendly, hostile;
};
struct guii {
	int					border;
	int					hero_size;
	int					padding;
	int					opacity;
	int					opacity_hilighted;
	int					tips_tab;
	int					tips_width;
	int					window_width;
	void				initialize();
};
class gamei : public resourceable {
	unsigned			round;
	unsigned			credits;
public:
	static variant		choose(const char* value, variant_s filter);
	void				passtime(int days);
	static bool			readf(const char* url);
	static result_s		roll(int dices);
};
extern gamei			game;
namespace draw {
void					initialize();
extern variants			objects;
void					setbackground(fnevent pf);
void					setbitmap(const char* id);
}
inline int				d100() { return rand() % 100; }
extern int				distance(point p1, point p2);
