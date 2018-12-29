#include "CommonFunction.h"
#include "CSprites.h"
#include <algorithm>
#include <stack>
#include <string>

void SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float &t, float &nx, float &ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}

bool AABBCheck(CDObject & M, CDObject & S)
{

	return (M.bottom() > S.top() && M.top() < S.bottom() && M.left() < S.right() && M.right() > S.left());

}

bool AABBCheckORI(LPGAMEOBJECT  M, LPGAMEOBJECT  S)
{
	float ml = 0.0f, mt = 0.0f, mr = 0.0f, mb = 0.0f;
	float dx = 0.0f, dy = 0.0f;
	float sl = 0.0f, st = 0.0f, sr = 0.0f, sb = 0.0f;

	M->GetBoundingBox(ml, mt, mr, mb);
	S->GetBoundingBox(sl, st, sr, sb);

	dx = M->dx;
	dy = M->dy;

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb)
		return false;
	return true;
	/*if (mb >= st && mt <= sb && ml <= sr && mr >= sl)
		return true;
	return false;*/
}

bool AABBCheckMoving(LPGAMEOBJECT M, LPGAMEOBJECT S)
{
	float ml = 0.0f, mt = 0.0f, mr = 0.0f, mb = 0.0f;
	float dx = 0.0f, dy = 0.0f;
	float sl = 0.0f, st = 0.0f, sr = 0.0f, sb = 0.0f;
	float dx2 = 0.0f, dy2 = 0.0f;

	M->GetBoundingBox(ml, mt, mr, mb);
	S->GetBoundingBox(sl, st, sr, sb);

	dx = M->dx;
	dy = M->dy;

	dx2 = S->dx;
	dy2 = S->dy;

	/*float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	float bls = dx2 > 0 ? sl : sl + dx;
	float bts = dy2 > 0 ? st : st + dy;
	float brs = dx2 > 0 ? sr + dx : sr;
	float bbs = dy2 > 0 ? sb + dy : sb;*/

	/*if (br < bls || bl > brs || bb < bts || bt > bbs)*/
	if (mr + dx < sl + dx2 || ml + dx > sr + dx2 || mb + dy < st + dy2 || mt + dy > sb + dy)
		return false;
	return true;
}

void DrawNumber(int number, float x, float y, int alpha)
{
	std::stack<int> holder;
	//std::vector<int>holder;
	int count = 0;
	while (number != 0) {
		int c;
		c = number % 10;
		number = number / 10;
		holder.push(c);
	}

	//std::reverse(holder.begin(), holder.end());

	if (holder.size() <= 0) {
		SPRITES->Get(6351)->Draw(x, y, 255);  //6351= NUM0
	}
	else {
		/*for (std::vector<int>::iterator it = holder.begin(); it != holder.end(); ++it) {
			SPRITES->Get(6351 + *it)->Draw(x + count * TEXT_NUMBER_SIZE, y, 255);
			count++;
		}*/
		while (holder.size() > 0) {
			int number = holder.top();
			SPRITES->Get(6351 + number)->Draw(x + count * TEXT_NUMBER_SIZE, y, 255);
			count++;
			holder.pop();
		}
	}

}


