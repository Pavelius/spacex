#include "answers.h"
#include "crt.h"
#include "dataset.h"
#include "point.h"
#include "stringbuilder.h"

#pragma once

enum variant_s : unsigned char {
	NoVariant,
	Action, Equipment, Fraction, Location, Planet, Size, Ship, Spaceunit, Squad, System, Visual
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
enum equipment_s : unsigned char {
	MachineGun, Laser, Rocket,
	Transponder,
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
	TerrainRealm, ColdRealm, SandRealm, WaterRealm, GasGiant, FoggyJungles, RockyRealm, CorrosiveHell,
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
enum protoship_s : unsigned char {
	Zond, Capsule, Shuttle, Fighter, Ranger, Interceptor, Battleship, Transporter,
	Cruiser, Carrier, Linkor, Dreadnought, Station,
};
enum action_s : unsigned char {
	Landing, Investigate, Flyup, SetCourse,
	GoingClose, GoingAway, ShootAll,
	SetConnection,
};
const int system_visibility_radius = 64;
typedef std::initializer_list<const char*> stringa;
typedef std::initializer_list<equipment_s> equipmenta;
typedef cflags<building_s> buildingf;
typedef cflags<fraction_s> fractionf;
struct statable : dataset<stat_s, HullDamage, unsigned short> {};
struct resourceable : dataset<resource_s, Drugs, int> {};
class shipi;
class rangei {
	unsigned char		value;
public:
	constexpr rangei() : value(0) {}
	constexpr rangei(std::initializer_list<int> v) : value(0) { for(auto e : v) set(e); }
	constexpr bool		is(int v) const { return (value & (1 << v)) != 0; }
	constexpr void		set(int v) { value |= 1 << v; }
};
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
	constexpr variant(int u) : u(u) {}
	constexpr variant(action_s v) : variant(Action, v) {}
	constexpr variant(equipment_s v) : variant(Equipment, v) {}
	variant(const char* v);
	variant(const void* v);
	constexpr operator int() const { return u; }
	constexpr explicit operator bool() const { return u != 0; }
	template<class T> operator T*() const { return (T*)((T::kind == c[3]) ? getpointer() : 0); }
	void				act(const char* format, ...) const;
	void				actv(stringbuilder& sb, const char* format, const char* format_param) const;
	void				clear() { u = 0; }
	int					getindex(int t) const { return (getkind() == t) ? getvalue() : 0; }
	void				getinfo(stringbuilder& sb) const;
	gender_s			getgender() const;
	void*				getpointer() const { return bsdata<varianti>::elements[c[3]].source->ptr(u & 0xFFFFFF); }
	constexpr variant_s	getkind() const { return (variant_s)c[3]; }
	const char*			getname() const;
	constexpr int		getvalue() const { return u & 0xFFFFFF; }
	void				paint() const;
	void				setvariant(unsigned char t, unsigned char v) { c[3] = t; c[0] = v; }
};
struct varianta {
	short unsigned		start;
	short unsigned		count;
	const variant*		begin() const { return bsdata<variant>::elements + start; }
	const variant*		end() const { return begin() + count; }
};
class datetime {
	constexpr static unsigned sy = 3000;
	constexpr static unsigned dpy = 12 * 30;
	unsigned			value;
public:
	constexpr static unsigned mpd = 24;
	constexpr datetime() : value(0) {}
	constexpr datetime(unsigned v) : value(v) {}
	constexpr datetime(int year, int month, int day) : value((year - sy)*(dpy*mpd)) {}
	constexpr explicit operator int() const { return value; }
	constexpr int		getday() const { return 1 + value / mpd; }
	constexpr int		getdayofmonth() const { return 1 + (value / mpd) % 30; }
	constexpr int		getmonth() const { return 1 + ((value / mpd) / 30) % 12; }
	const char*			getname() const;
	constexpr int		getyear() const { return sy + value / (dpy * mpd); }
};
struct damagei {
	unsigned char		hits[2];
	unsigned char		count;
	unsigned char		range;
	int					roll(int chance_critical = 0) const;
	void				upgrade(equipment_s type, int power);
};
class object : public variant {
	struct {
		unsigned char	power : 3;
		fraction_s		origin : 3;
		unsigned char	variation : 2;
	};
	unsigned char		used;
	unsigned char		weight;
public:
	constexpr object() : variant(), power(0), origin(), variation(), used(), weight() {}
	object(equipment_s type, fraction_s origin = Independed, int power = 0) { create(type, origin, power); }
	void				create(equipment_s type, fraction_s origin, int power);
	int					getcount() const { return 1; }
	damagei				getdamage() const;
	int					getpower() const { return power; }
	int					getweight() const { return weight * getcount(); }
	int					getusemaximum() const;
	bool				iseffective(int range) const;
	bool				isweapon() const;
	void				use() { used++; }
};
struct equipmenti {
	static const variant_s kind = Equipment;
	const char*			id;
	const char*			name;
	damagei				damage;
	short				weight[2];
	rangei				range;
	constexpr bool		iseffective(int v) const { return range.is(v); }
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
struct locationi {
	const char*			id;
	const char*			name;
};
struct landscapei {
	const char*			id;
	const char*			name;
	const char*			text;
	stringa				background;
	const char*			getbackground(unsigned seed) const;
};
struct sizei {
	const char*			id;
	const char*			name;
};
struct populationi {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct actioni {
	const char*			id;
	const char*			name;
};
struct nameable {
	const char*			id;
	const char*			name;
	const char*			getname() const { return name; }
};
struct planeti : nameable {
	static const variant_s kind = Planet;
	fraction_s			fraction;
	point				position;
	variant				parent;
	population_s		population;
	landscape_s			landscape;
	size_s				size;
	constexpr explicit operator bool() const { return position.operator bool(); }
	const char*			getbackground() const { return bsdata<landscapei>::elements[landscape].getbackground(bsdata<planeti>::source.indexof(this)); }
	void				getinfo(stringbuilder& sb) const;
	void				paint() const;
};
struct systemi {
	static const variant_s kind = System;
	const char*			id;
	const char*			name;
	void				getinfo(stringbuilder& sb) const;
	void				paint() const;
};
struct variants : adat<variant, 128> {
	void				addships(variant vs);
	void				addspaceunits();
	void				addplanets(variant vs);
	variant				choose(const char* title, bool interactive, bool chooseone) const;
	void				matchaggressive(bool keep);
	void				matchships(point fp, int r, bool keep, bool apply_transponder);
	void				paint() const;
};
struct objectable : adat<object, 32> {
};
class waitable {
	unsigned			stamp;
public:
	bool				iswait() const;
	void				wait(unsigned hours);
	void				wakeup() { stamp = 0; }
};
class moveable {
	point				position, start_position, target_position;
	unsigned			start_date;
public:
	point				getposition() const { return position; }
	point				getdestination() const { return target_position; }
	bool				ismoving() const;
	bool				moving(int velocity, unsigned stamp);
	void				setmovement(point v, unsigned start_date);
	void				setposition(point v);
	void				setposition(variant v);
	void				stop();
};
struct protoshipi {
	const char*			id;
	const char*			name;
	short				crew;
	short				hull;
	short				speed;
	equipmenta			equipments;
};
class orderable : adat<variant, 2> {
public:
	void				addorder(variant v) { add(v); }
	variant				getorder() const { return data[0]; }
	bool				isorder() const { return operator bool(); }
	void				removeorder() { remove(0, 1); }
};
struct equipmentq : adat<object*, 128> {
	void				matchef(variants& source, bool keep);
};
class shipi : public statable, public moveable, public waitable, public orderable {
	statable			basic;
	protoship_s			type;
	fraction_s			fraction;
	variant				parent;
	objectable			objects;
	short unsigned		name, name_index;
public:
	static const variant_s kind = Ship;
	constexpr explicit operator bool() const { return parent; }
	void				add(const object& v);
	void				apply(variant v, bool interactive);
	void				chatting(shipi* opponent, bool interactive);
	void				clear();
	void				create(protoship_s type);
	variant				chooseaction(bool interactive, bool paused);
	void				flyup();
	void				getinfo(stringbuilder& sb) const;
	const char*			getkindname() const;
	variant				getlocation() const { return parent; }
	const char*			getname() const;
	planeti*			getplanet() const;
	int					getvelocity() const;
	void				getweapons(equipmentq& result, int range);
	void				hit(damagei& damage);
	void				investigate();
	bool				is(equipment_s v) const;
	bool				isalive() const { return get(HullDamage) < get(Hull); }
	bool				iseffective(int range) const;
	bool				isplayer() const;
	void				landing();
	void				maketurn(bool interactive);
	void				paint(int x, int y) const;
	void				paint() const { paint(getposition().x, getposition().y); }
	void				setconnection(bool interactive);
	void				setcourse(bool interactive);
	void				setlocation(variant v) { parent = v; }
	void				shoot(object& weapon, shipi& enemy);
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
struct visuali : variant, moveable {
	void				paint() const;
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
class spaceunit : public moveable {
	static unsigned		animation_stamp;
	shipi*				ship;
	shipi*				target;
	char				range;
	bool				aggressor;
public:
	static const variant_s kind = Spaceunit;
	constexpr spaceunit() : moveable(), ship(0), target(0), range(0), aggressor(false) {}
	constexpr explicit operator bool() const { return ship != 0; }
	static void			add(shipi* p, bool aggressor);
	void				apply(variant v, bool interactive);
	static void			battle();
	variant				chooseaction(bool interactive) const;
	spaceunit*			chooseenemy(bool interactive) const;
	static void			cleanup();
	void				clear();
	bool				isaggressor() const { return aggressor; }
	bool				isplayer() const { return ship->isplayer(); }
	int					getrange() const { return range; }
	shipi*				getship() { return ship; }
	shipi*				gettarget() { return target; }
	void				maketurn();
	static void			moveall();
	void				paint() const;
	variants			select(bool agressive) const;
	void				setagressor(bool v) { aggressor = v; }
	void				setrange(int v);
	void				settarget(shipi* v) { target = v; }
	void				shoot(spaceunit& enemy);
	static void			startbattle();
	void				wait();
	static void			waitall();
};
class gamei : public resourceable {
	unsigned			round;
	unsigned			credits;
public:
	datetime			getdate() const { return round; }
	static shipi*		getplayer();
	unsigned			getround() const { return round; }
	static void			message(bool interactive, const char* format, const char* resid);
	static void			passhour();
	void				passtime(int days);
	static void			play(fnevent timer);
	static int			random(int v1, int v2) { return xrand(v1, v2); }
	static int			random(int v1, int v2, int c);
	static bool			readf(const char* url);
	static result_s		roll(int dices);
};
extern gamei			game;
namespace draw {
void					application();
void					initialize();
fnevent					getbackground();
void					setbackground(fnevent pv);
void					setbitmap(const char* id);
void					setnext(fnevent pv);
}
inline int				d100() { return rand() % 100; }
extern int				distance(point p1, point p2);