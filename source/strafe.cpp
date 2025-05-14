#include "client.h"
const float MAX_POSSIBLE_DISTANCE = 8192.f;
float FrameCount;
float FpsCount;
float InterpFps;
float PreStrafe;
float JumpOff;

float Keyforwardm = false;
float Keymoveleft = false;
float Keymoveright = false;
float Keyback = false;
float Keyduck = false;
float Keyjump = false;
bool Strafe = false;
bool Fastrun = false;
bool Gstrafe = false;
bool Bhop = false;
bool Jumpbug = false;

bool AllGo = false;
bool BhopModul = false;
bool autotongbu = false;
bool Start = false;
bool Mscj = false;
bool speed278 = false;
bool Super = false;
bool DTGL = false;
bool XXTS = false;
bool QHZY = false;
bool kakong = false;
bool DSRC = false;

float YawForVec(float* fwd)
{
	if (fwd[1] == 0 && fwd[0] == 0)
		return 0;
	else
	{
		float yaw = (atan2(fwd[1], fwd[0]) * 180 / M_PI);
		if (yaw < 0)yaw += 360;
		return yaw;
	}
}

//void StrafeHack(float frametime, struct usercmd_s *cmd)
//{
//	if(Strafe && !(g_Local.iFlags & FL_ONGROUND) && (g_Local.iMovetype != MOVETYPE_FLY) && !(cmd->buttons&IN_ATTACK) && !(cmd->buttons & IN_ATTACK2 && IsCurWeaponKnife()))
//	{
//		if(g_Local.flVelocityspeed < 15)
//		{	
//			cmd->forwardmove=400;
//			cmd->sidemove=0;
//		}
//
//		float dir = 0;
//		if (cmd->buttons & IN_MOVERIGHT)
//			dir = 90;
//		if (cmd->buttons & IN_BACK)
//			dir = 180;
//		if (cmd->buttons & IN_MOVELEFT)
//			dir = -90;
//
//		Vector va_real;
//		g_Engine.GetViewAngles(va_real);
//		va_real.y+=dir;
//		float vspeed[3]={ g_Local.vVelocity.x/g_Local.flVelocity,g_Local.vVelocity.y/g_Local.flVelocity,0.0f};
//		float va_speed=YawForVec(vspeed);
//		float adif=va_speed-va_real[1];
//		while(adif<-180)adif+=360;
//		while(adif>180)adif-=360;
//		cmd->sidemove=(437.8928)*(adif>0?1:-1);
//		cmd->forwardmove=0;
//		bool onlysidemove=(abs(adif)>=atan(30.f/g_Local.flVelocityspeed)/M_PI*180);
//		cmd->viewangles[1] -= (-adif); 
//		float fs = 0;
//		if(!onlysidemove)
//		{
//			static float lv=0;
//			Vector fw=g_Local.vStrafeForward;fw[2]=0;fw=fw.Normalize();
//			float vel=POW(fw[0]* g_Local.vVelocity[0])+POW(fw[1]* g_Local.vVelocity[1]);
//
//			fs=lv;
//			lv=sqrt(69.f * 100000 / vel);
//			static float lastang=0;
//			float ca=abs(adif);		
//			lastang=ca;
//		}
//
//		float ang = atan(fs/cmd->sidemove)/M_PI*180;
//		cmd->viewangles.y+=ang;
//
//		float sdmw=cmd->sidemove;
//		float fdmw=cmd->forwardmove;
//
//		if(cmd->buttons & IN_MOVERIGHT)
//		{
//			cmd->forwardmove = -sdmw;
//			cmd->sidemove = fdmw;
//		}
//		if(cmd->buttons & IN_BACK)
//		{
//			cmd->forwardmove = -fdmw;
//			cmd->sidemove = -sdmw;
//		}
//		if(cmd->buttons & IN_MOVELEFT)
//		{
//			cmd->forwardmove = sdmw;
//			cmd->sidemove = -fdmw;
//		}
//	}
//}

void StrafeHack(struct usercmd_s* cmd)
{
	if (GetAsyncKeyState(0x46) && !(pmove->flags & FL_ONGROUND) || GetAsyncKeyState(0x46) && !(pmove->flags & FL_ONGROUND) || GetAsyncKeyState(VK_SHIFT) && !(pmove->flags & FL_ONGROUND))
	{
		float dir = 0.0f;


		int dir_value = 1;
		if (cmd->buttons & IN_MOVERIGHT)
			dir_value = 2;
		if (cmd->buttons & IN_BACK)
			dir_value = 3;
		if (cmd->buttons & IN_MOVELEFT)
			dir_value = 4;

		if (dir_value == 1)dir = 0 * M_PI / 180.0f;
		else if (dir_value == 2)	dir = 90 * M_PI / 180.0f;
		else if (dir_value == 3)	dir = 180 * M_PI / 180.0f;
		else if (dir_value == 4)	dir = -90 * M_PI / 180.0f;




		//if (g_Local.fSpeed < 15.0f)
		if (sqrt(POW(pmove->velocity[0]) + POW(pmove->velocity[1])) < 15)
		{
			if (cmd->buttons & IN_FORWARD)
			{
				if (cmd->buttons & IN_MOVELEFT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons & IN_MOVERIGHT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = 900;
			}
			else if (cmd->buttons & IN_BACK)
			{
				if (cmd->buttons & IN_MOVELEFT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons & IN_MOVERIGHT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = -900;
			}
			else if (cmd->buttons & IN_MOVELEFT)
				cmd->sidemove = -900;
			else if (cmd->buttons & IN_MOVERIGHT)
				cmd->sidemove = 900;
			else
				cmd->forwardmove = 900;
		}
		else
		{
			float va_speed = atan2(pmove->velocity.y, pmove->velocity.x);

			float va[3] = {};
			g_Engine.GetViewAngles(va);

			float adif = va_speed - va[1] * M_PI / 180.0f - dir;

			adif = sin(adif);
			adif = atan2(adif, sqrt(1 - adif * adif));

			cmd->sidemove = (437.8928) * (adif > 0 ? 1 : -1);
			cmd->forwardmove = 0;

			float angle;
			float osin, ocos, nsin, ncos;

			angle = cmd->viewangles.y * M_PI / 180.0f;
			osin = sin(angle);
			ocos = cos(angle);

			angle = 2.0f * cmd->viewangles.y * M_PI / 180.0f - va_speed + dir;
			nsin = sin(angle);
			ncos = cos(angle);

			cmd->forwardmove = cmd->sidemove * (osin * ncos - ocos * nsin);
			cmd->sidemove *= osin * nsin + ocos * ncos;

			float fs = 0;
			if (atan2(10000 / va_speed, 1.0f) >= abs(adif))
			{
				Vector vBodyDirection;

				if (dir_value & 1)
					vBodyDirection = pmove->forward;
				else
					vBodyDirection = pmove->right;

				vBodyDirection[2] = 0;
				vBodyDirection = vBodyDirection.Normalize();

				float vel = POW(vBodyDirection[0] * pmove->velocity[0]) + POW(vBodyDirection[1] * pmove->velocity[1]);

				fs = sqrt(69.0 * 100000 / vel);
			}

			cmd->forwardmove += fs / 2;
		}

		float sdmw = cmd->sidemove;
		float fdmw = cmd->forwardmove;

		switch (dir_value)
		{
		case 1:
			cmd->forwardmove = fdmw;
			cmd->sidemove = sdmw;
			break;
		case 2:
			cmd->forwardmove = -sdmw;
			cmd->sidemove = fdmw;
			break;
		case 3:
			cmd->forwardmove = -fdmw;
			cmd->sidemove = -sdmw;
			break;
		case 4:
			cmd->forwardmove = sdmw;
			cmd->sidemove = -fdmw;
			break;
		}

	}
}

void StrafeHack2(struct usercmd_s* cmd)
{
	if (GetAsyncKeyState(VK_SPACE) && !(*(ULONG*)((char*)pmove + 0xC8) == 0x208) || GetAsyncKeyState(VK_MENU) && !(*(ULONG*)((char*)pmove + 0xC8) == 0x208) || GetAsyncKeyState(VK_SHIFT) && !(*(ULONG*)((char*)pmove + 0xC8) == 0x208))
	{
		float dir = 0.0f;


		int dir_value = 1;
		if (cmd->buttons & IN_MOVERIGHT)
			dir_value = 2;
		if (cmd->buttons & IN_BACK)
			dir_value = 3;
		if (cmd->buttons & IN_MOVELEFT)
			dir_value = 4;

		if (dir_value == 1)dir = 0 * M_PI / 180.0f;
		else if (dir_value == 2)	dir = 90 * M_PI / 180.0f;
		else if (dir_value == 3)	dir = 180 * M_PI / 180.0f;
		else if (dir_value == 4)	dir = -90 * M_PI / 180.0f;




		//if (g_Local.fSpeed < 15.0f)
		if (sqrt(POW(pmove->velocity[0]) + POW(pmove->velocity[1])) < 15)
		{
			if (cmd->buttons & IN_FORWARD)
			{
				if (cmd->buttons & IN_MOVELEFT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons & IN_MOVERIGHT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = 900;
			}
			else if (cmd->buttons & IN_BACK)
			{
				if (cmd->buttons & IN_MOVELEFT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons & IN_MOVERIGHT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = -900;
			}
			else if (cmd->buttons & IN_MOVELEFT)
				cmd->sidemove = -900;
			else if (cmd->buttons & IN_MOVERIGHT)
				cmd->sidemove = 900;
			else
				cmd->forwardmove = 900;
		}
		else
		{
			float va_speed = atan2(pmove->velocity.y, pmove->velocity.x);

			float va[3] = {};
			g_Engine.GetViewAngles(va);

			float adif = va_speed - va[1] * M_PI / 180.0f - dir;

			adif = sin(adif);
			adif = atan2(adif, sqrt(1 - adif * adif));

			cmd->sidemove = (437.8928) * (adif > 0 ? 1 : -1);
			cmd->forwardmove = 0;

			float angle;
			float osin, ocos, nsin, ncos;

			angle = cmd->viewangles.y * M_PI / 180.0f;
			osin = sin(angle);
			ocos = cos(angle);

			angle = 2.0f * cmd->viewangles.y * M_PI / 180.0f - va_speed + dir;
			nsin = sin(angle);
			ncos = cos(angle);

			cmd->forwardmove = cmd->sidemove * (osin * ncos - ocos * nsin);
			cmd->sidemove *= osin * nsin + ocos * ncos;

			float fs = 0;
			if (atan2(10000 / va_speed, 1.0f) >= abs(adif))
			{
				Vector vBodyDirection;

				if (dir_value & 1)
					vBodyDirection = pmove->forward;
				else
					vBodyDirection = pmove->right;

				vBodyDirection[2] = 0;
				vBodyDirection = vBodyDirection.Normalize();

				float vel = POW(vBodyDirection[0] * pmove->velocity[0]) + POW(vBodyDirection[1] * pmove->velocity[1]);

				fs = sqrt(69.0 * 100000 / vel);
			}

			cmd->forwardmove += fs / 2;
		}

		float sdmw = cmd->sidemove;
		float fdmw = cmd->forwardmove;

		switch (dir_value)
		{
		case 1:
			cmd->forwardmove = fdmw;
			cmd->sidemove = sdmw;
			break;
		case 2:
			cmd->forwardmove = -sdmw;
			cmd->sidemove = fdmw;
			break;
		case 3:
			cmd->forwardmove = -fdmw;
			cmd->sidemove = -sdmw;
			break;
		case 4:
			cmd->forwardmove = sdmw;
			cmd->sidemove = -fdmw;
			break;
		}

	}
}

void FastRun(struct usercmd_s* cmd)
{
	if (GetAsyncKeyState(0x57) && sqrt(POW(pmove->velocity[0]) + POW(pmove->velocity[1])) && pmove->flFallVelocity == 0 && !Gstrafe && pmove->flags & FL_ONGROUND)
	{
		static bool Run = false;
		if ((cmd->buttons & IN_FORWARD && cmd->buttons & IN_MOVELEFT) || (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVERIGHT))
		{
			if (Run)
			{
				Run = false;
				cmd->sidemove -= 89.6f;
				cmd->forwardmove -= 89.6f;
			}
			else
			{
				Run = true;
				cmd->sidemove += 89.6f;
				cmd->forwardmove += 89.6f;
			}
		}
		else if ((cmd->buttons & IN_FORWARD && cmd->buttons & IN_MOVERIGHT) || (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVELEFT))
		{
			if (Run)
			{
				Run = false;
				cmd->sidemove -= 89.6f;
				cmd->forwardmove += 89.6f;
			}
			else
			{
				Run = true;
				cmd->sidemove += 89.6f;
				cmd->forwardmove -= 89.6f;
			}
		}
		else if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK)
		{
			if (Run)
			{
				Run = false;
				cmd->sidemove -= 126.6f;
			}
			else
			{
				Run = true;
				cmd->sidemove += 126.6f;
			}
		}
		else if (cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
		{
			if (Run)
			{
				Run = false;
				cmd->forwardmove -= 126.6f;
			}
			else
			{
				Run = true;
				cmd->forwardmove += 126.6f;
			}
		}
	}
}

void BHop(struct usercmd_s* cmd)
{
	if (g_InFocus)
	{
		if (pmove->flags & FL_INWATER || pmove->flags & FL_ONGROUND || pmove->waterlevel >= 2 || pmove->movetype == 5)
		{
			cmd->buttons |= IN_JUMP;
		}
		else
		{
			cmd->buttons &= ~IN_JUMP;
		}
	}
}

int temp4 = 0;
//DWORD time_a2 = 0;
bool last_duck = false;
bool duck2 = false;
void BHop2(struct usercmd_s* cmd)
{
	if (duck2)
	{
		AdjustSpeed(1.5);
		cmd->buttons &= ~IN_DUCK;
		duck2 = false;
		return;
	}
	if (pmove->flags & FL_ONGROUND)
	{
		AdjustSpeed(1.4);
		cmd->buttons |= IN_DUCK;
		duck2 = true;
		if (Super)
		{
			AdjustSpeed(0.000001);
		}
		return;
	}
		}



	void BHop3(struct usercmd_s* cmd)
	{
		cmd->buttons &= ~IN_JUMP;
		cmd->buttons |= IN_DUCK;
		if (*(ULONG*)((char*)pmove + 0xC8) == 0x208)
		{
			cmd->buttons |= IN_JUMP;
		}

		if (*(ULONG*)((char*)pmove + 0xAC) < 0x20000000)
		{
			cmd->buttons &= ~IN_DUCK;
			cmd->buttons |= IN_JUMP;
		}
	}



	/*if (last_duck)
	{
		if (*(ULONG*)((char*)pmove + 0xC8) == 0x208)
		{
			cmd->buttons &= ~IN_DUCK;
		}
		last_duck = !last_duck;
	}
	else
	{

		if (*(ULONG*)((char*)pmove + 0xC8) == 0x208)
		{
			cmd->buttons |= IN_DUCK;
		}
		last_duck = !last_duck;
	}*/

	//time_a = GetTickCount();

	//if (temp4 < temp3)
	/*if (temp4 < 8)
	{
		temp4++;
		return;
	}
	temp4 = 0;
	if (last_duck)
	{
		cmd->buttons &= ~IN_DUCK;
		last_duck = !last_duck;
	}
	else
	{
		cmd->buttons |= IN_DUCK;
		last_duck = !last_duck;
	}*/
	//cmd->buttons &= ~IN_DUCK;
	//if (pmove->flags & FL_ONGROUND)
	//if (GetTickCount() - time_a2 > temp3)
	//{
	//	time_a = GetTickCount();
	//	cmd->buttons |= IN_DUCK;
	//}


void AutoATK(struct usercmd_s* cmd)
{
	if (g_InFocus)
	{
		if (pmove->flags & FL_ONGROUND || pmove->waterlevel >= 2 || pmove->movetype == 5)
		{
			cmd->buttons |= IN_ATTACK2;
		}
		else
		{

		}
	}
}

void GroundStrafe(struct usercmd_s* cmd) {
	static bool in_gs = false;//&& g::InFocus
	if (GetAsyncKeyState(VK_LMENU) && g_InFocus) {
		// compute some stuff needed only for GroundStrafe inside 'GroundStrafe' function
		pmtrace_t* trace = g_Engine.PM_TraceLine(pmove->origin, Vector(pmove->origin.x, pmove->origin.y, -MAX_POSSIBLE_DISTANCE), 1, (pmove->flags & FL_DUCKING) ? 1 : 0, -1);
		float height = abs(trace->endpos.z - pmove->origin.z);
		float groundAngle = acos(trace->plane.normal[2]) / M_PI * 180;
		float xy_speed = sqrt(POW(pmove->velocity[0]) + POW(pmove->velocity[1]));
		static int gs_state = 0;
		in_gs = true;

		// there are 4 similar types of GroundStrafe.
		// some of them made no sense to implement,
		// because they are noticeably slower than other.
		// approximate speed measurements:
		// GS       - 700 u/s	
		// Jump GS  - 750 u/s
		// SGS      - 600 u/s
		// Jump SGS - 650 u/s
		//0xAC flFallVelocity
		//D("结构虚表:%p", g::pPlayerMove);

		//if (pmove->flFallVelocity > 0) {
		//	if (groundAngle < 5.0f && ((pmove->flags & FL_ONGROUND) || height < 0.00001f))
		//	{
		//		AdjustSpeed(0.0000001f);
		//	}
		//	if (pmove->flFallVelocity >= 100)
		//	{
		//		if (height <= 30)
		//		{
		//			//ActivateKey(g::pButtonsBits->duck);
		//			cmd->buttons |= IN_DUCK;
		//		}
		//	}
		//}


		if (gs_state == 0 && (pmove->flags & FL_ONGROUND)) {
			if (groundAngle < 5.0f && ((pmove->flags & FL_ONGROUND) || height < 0.000001f))
				cmd->buttons |= IN_DUCK;
			//ActivateKey(g::pButtonsBits->duck);
			gs_state = 1;
		}
		else if (gs_state == 1) {
			if (groundAngle < 5.0f && ((pmove->flags & FL_ONGROUND) || height < 0.000001f))
			{
			}
			cmd->buttons &= ~IN_DUCK;
			//DeactivateKey(g::pButtonsBits->duck);
			//if (GsModul == 2 || GsModul == 3 && ((pmove->flags & FL_DUCKING) ? 1 : 0) == 0)
			//{
			//	ActivateKey(g::pButtonsBits->jump);
			//	//cmd->buttons |= IN_JUMP;
			//}
			gs_state = 0;
		}
	}
	// this piece of code is needed to prevent
	// 'sticking' of duck/jump when gs is stopped
	else if (in_gs) {
		cmd->buttons &= ~IN_DUCK;
		cmd->buttons &= ~IN_JUMP;
		in_gs = false;
	}
}

void GroundStrafeMSCJ(struct usercmd_s* cmd) {
	static bool in_gs = false;//&& g::InFocus
	if (GetAsyncKeyState(VK_SHIFT) && g_InFocus) {
		// compute some stuff needed only for GroundStrafe inside 'GroundStrafe' function
		pmtrace_t* trace = g_Engine.PM_TraceLine(pmove->origin, Vector(pmove->origin.x, pmove->origin.y, -MAX_POSSIBLE_DISTANCE), 1, (pmove->flags & FL_DUCKING) ? 1 : 0, -1);
		float height = abs(trace->endpos.z - pmove->origin.z);
		float groundAngle = acos(trace->plane.normal[2]) / M_PI * 180;
		float xy_speed = sqrt(POW(pmove->velocity[0]) + POW(pmove->velocity[1]));
		static int gs_state = 0;
		in_gs = true;


		if (pmove->flFallVelocity >= 100)
			if (height <= 140)
				cmd->buttons |= IN_DUCK;

		if (gs_state == 0 && (pmove->flags & FL_ONGROUND)) {
			if (groundAngle < 5.0f && ((pmove->flags & FL_ONGROUND) || height < 0.000001f))
				AdjustSpeed(0.5);//不限速0.000001f  限速0.5f
			cmd->buttons |= IN_DUCK;
			//ActivateKey(g::pButtonsBits->duck);
			gs_state = 1;
		}
		else if (gs_state == 1) {
			if (groundAngle < 5.0f && ((pmove->flags & FL_ONGROUND) || height < 0.000001f))
			{
				AdjustSpeed(0.5);
			}
			cmd->buttons &= ~IN_DUCK;
			//DeactivateKey(g::pButtonsBits->duck);
			//if (GsModul == 2 || GsModul == 3 && ((pmove->flags & FL_DUCKING) ? 1 : 0) == 0)
			//{
			//	ActivateKey(g::pButtonsBits->jump);
			//	//cmd->buttons |= IN_JUMP;
			//}
			gs_state = 0;
		}
	}
	// this piece of code is needed to prevent
	// 'sticking' of duck/jump when gs is stopped
	else if (in_gs) {
		cmd->buttons &= ~IN_DUCK;
		cmd->buttons &= ~IN_JUMP;
		in_gs = false;
	}
}

//void GroundStrafe(struct usercmd_s *cmd)
//{
//	if(Gstrafe && !Jumpbug)
//	{
//		static int gs_state = 0;
//		if(gs_state == 0 && g_Local.iFlags&FL_ONGROUND)
//		{
//			cmd->buttons |=IN_DUCK;
//			gs_state = 1;
//		}
//		else if(gs_state == 1)
//		{
//			cmd->buttons &= ~IN_DUCK;
//			gs_state = 0;
//		}
//	}
//}
//
//void BHop(float frametime, struct usercmd_s *cmd)
//{
//	static bool lastFramePressedJump=false;
//	static bool JumpInNextFrame=false;
//	static float kz_bhop_cnt_rand_min = 0.f;
//	static float kz_bhop_cnt_rand_max = 12.f;
//	static int inAirBhopCnt = 0;
//
//	bool isJumped = false;
//
//	if(JumpInNextFrame)
//	{
//		JumpInNextFrame=false;
//		cmd->buttons|=IN_JUMP;
//		goto bhopfuncend;
//	}
//	if(Bhop && !Gstrafe)
//	{
//		cmd->buttons &= ~IN_JUMP;
//		if(((!lastFramePressedJump)|| g_Local.iFlags&FL_ONGROUND || g_Local.flWaterlevel >= 2 || g_Local.iMovetype == MOVETYPE_FLY || g_Local.flHeightorigin<=2) && !Jumpbug)
//		{
//			static int bhop_jump_number = 0;
//			bhop_jump_number++;
//			if (bhop_jump_number >= 2)
//			{
//				bhop_jump_number = 0;
//				JumpInNextFrame = true;
//				goto bhopfuncend;
//			}
//
//			if(kz_bhop_cnt_rand_min > kz_bhop_cnt_rand_max)
//				kz_bhop_cnt_rand_min = kz_bhop_cnt_rand_max;
//
//			if(kz_bhop_cnt_rand_min <= 1)
//				kz_bhop_cnt_rand_min = 1;
//
//			if(kz_bhop_cnt_rand_min > 20)
//				kz_bhop_cnt_rand_min = 20;
//
//			if(kz_bhop_cnt_rand_max > 20)
//				kz_bhop_cnt_rand_max = 20;
//
//			if(kz_bhop_cnt_rand_max <= 1)
//				kz_bhop_cnt_rand_max = 1;
//
//			inAirBhopCnt = (int)g_Engine.pfnRandomFloat((int)kz_bhop_cnt_rand_min,(int)kz_bhop_cnt_rand_max);
//
//			isJumped=true;
//			cmd->buttons |= IN_JUMP;
//		} 
//	}
//	if(!isJumped)
//	{
//		if(inAirBhopCnt>0)
//		{
//			if(inAirBhopCnt%2==0) 
//			{
//				cmd->buttons |= IN_JUMP;
//			}
//			else cmd->buttons &= ~IN_JUMP;
//			inAirBhopCnt--;
//		}
//	}
//    bhopfuncend:
//	lastFramePressedJump = cmd->buttons&IN_JUMP;
//}



double _my_abs(double n)
{
	if (n >= 0)return n; //if positive, return without ant change
	else return 0 - n; //if negative, return a positive version
}

void JumpBug(float frametime, struct usercmd_s* cmd)
{
	static int state = 0;

	bool autojb = false;
	if (cvar.kz_jump_bug_auto && g_Local.flFallVelocity >= 404.8f)
		if (g_Local.flHeightorigin - (g_Local.flFallVelocity * frametime / cvar.misc_wav_speed * 15) <= 0)
			autojb = true;

	if ((Jumpbug || autojb) && g_Local.flFallVelocity > 0)
	{
		bool curveang = false;
		float fpheight = 0;
		if (g_Local.flGroundangle > 1)
		{
			curveang = true;
			Vector vTemp = g_Local.vOrigin;
			vTemp[2] -= 8192;
			pmtrace_t* trace = g_pEngine->PM_TraceLine(g_Local.vOrigin, vTemp, 1, 2, -1);
			fpheight = abs(g_Local.vOrigin.z - trace->endpos.z - (g_Local.iUsehull == 1 ? 18.0f : 36.0f));
		}
		else fpheight = g_Local.flHeightorigin;


		static float last_h = 0.0f;
		float cur_frame_zdist = abs((g_Local.flFallVelocity + (800 * frametime)) * frametime);
		cmd->buttons |= IN_DUCK;
		cmd->buttons &= ~IN_JUMP;
		switch (state)
		{
		case 1:
			cmd->buttons &= ~IN_DUCK;
			cmd->buttons |= IN_JUMP;
			state = 2;
			break;
		case 2:
			state = 0;
			break;
		default:
			if (_my_abs(fpheight - cur_frame_zdist * 1.5) <= (20.0) && cur_frame_zdist > 0.0f)
			{
				float needspd = _my_abs(fpheight - (19.0));
				float scale = abs(needspd / cur_frame_zdist);
				AdjustSpeed(scale);
				state = 1;
			}
			break;
		}
		last_h = fpheight;
	}
	else state = 0;
}

//bool ChatWindow()  //判断聊天窗口 ESC 等是否打开
////聊天窗口或者ESC打开，字节搜索1，关闭搜索0，重复步骤，找到基址为止。
//{
//	ULONG temp_addr2 = (ULONG)GetModuleHandleA("hw.dll");
//	temp_addr2 += 0x48E16A;   //聊天窗口等开关基址
//
//	// 将ULONG类型指针转换为int*类型指针  
//	int* address = (int*)temp_addr2;
//
//	// 解引用指针获取地址处的值  
//	int value = *address;
//	if (value == 65793)  //如果聊天窗口打开，kz功能失效
//	{
//		return false;
//	}
//	else if (value == 65792)   //如果聊天窗口关闭，kz功能正常使用
//	{
//		return true;
//	}
//}
//
//bool isWindowActive()
//
////当前游戏窗口
//{
//	ULONG temp_addr2 = (ULONG)GetModuleHandleA("client.dll");
//	temp_addr2 += 0x370674;   //游戏窗口基址
//
//	// 将ULONG类型指针转换为int*类型指针  
//	int* address = (int*)temp_addr2;
//
//	// 解引用指针获取地址处的值  
//	int value = *address;
//	if (value == 0)  //非游戏窗口激活，kz功能失效
//	{
//		return false;
//	}
//	else if (value == 1)   //游戏窗口激活，kz功能正常使用
//	{
//		return true;
//	}
//}


void DTGL_()
{
	//地图高亮 0F BE 84 32 ???????? 
	if (DTGL)
	{
		ULONG temp_addr2 = (ULONG)GetModuleHandleA("hw.dll");
		temp_addr2 += 0x1E6D384;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 256;//开启地图高亮
	}
	else
	{
		ULONG temp_addr2 = (ULONG)GetModuleHandleA("hw.dll");
		temp_addr2 += 0x1E6D384;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 108;//关闭地图高亮
	}
}

void XXTS_()
{
	if (XXTS)
	{
	
		ULONG temp_addr2 = (ULONG)GetModuleHandleA("client.dll");
		temp_addr2 += 0x3D6254;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 257;//显血
		g_Engine.pfnClientCmd((char*)"cl_headname 1;");//--显示队友头顶ID指令

		temp_addr2 = (ULONG)GetModuleHandleA("hw.dll");
		temp_addr2 += 0x12D25F8;
		temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 2;//房间设置全显

	}
	else
	{

		ULONG temp_addr2 = (ULONG)GetModuleHandleA("client.dll");
		temp_addr2 += 0x3D6254;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 256;//关闭显血


		temp_addr2 = (ULONG)GetModuleHandleA("hw.dll");
		temp_addr2 += 0x12D25F8;
		temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 0;//房间设置全显关闭
	}
}


void DSRC_()
{
	if (DSRC)
	{

		ULONG temp_addr2 = (ULONG)GetModuleHandleA("client.dll");
		temp_addr2 += 0x4B4CC8;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 1;//第三人称视角
		g_Engine.pfnClientCmd((char*)"cam_idealdist 150;cam_idealyaw 0");//--第三人称视角修复
	}
	else
	{

		ULONG temp_addr2 = (ULONG)GetModuleHandleA("client.dll");
		temp_addr2 += 0x4B4CC8;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 0;//关闭
	}
}



void QHZY_()
{
	if (QHZY)
	{
		ULONG temp_addr2 = (ULONG)GetModuleHandleA("client.dll");
		temp_addr2 += 0x36DCAC;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 1;//显名T
	}
	else
	{
		ULONG temp_addr2 = (ULONG)GetModuleHandleA("client.dll");
		temp_addr2 += 0x36DCAC;
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 2;//显名CT
	}
}



void Kz(float frametime, struct usercmd_s* cmd)
{
	//if (ChatWindow())
	//if (isWindowActive())
	{
	if (GetAsyncKeyState(VK_F8) & 1)
	{
		AllGo = !AllGo;
	}
	if (GetAsyncKeyState(VK_F12) & 1)
	{
		Mscj = !Mscj;
	}
	if (GetAsyncKeyState(VK_F10) & 1)
	{
		speed278 = !speed278;
	}
	//if (GetAsyncKeyState(VK_F9) & 1)
	//{
	//	autotongbu = !autotongbu;
	//}
	if (GetAsyncKeyState(VK_F11) & 1)
	{
		Super = !Super;
	}
	if (GetAsyncKeyState(0x38) & 1)// 8 地图高亮
	{
		DTGL = !DTGL;
	}
	if (GetAsyncKeyState(VK_F5) & 1)// F5 显血名透视
	{
		XXTS = !XXTS;
	}
	if (GetAsyncKeyState(0x5A) & 1)// Z 切换显血名阵营
	{
		QHZY = !QHZY;
	}
	if (GetAsyncKeyState(0x30) & 1)// 第三人称
	{
		DSRC = !DSRC;
	}

	//if (GetAsyncKeyState(VK_F3) & 1)
	//{
	//	g_Engine.pfnClientCmd((char*)"gl_fog 0; fps_max 101;AK47L;Deagled;svdex;bazooka;");
	//}
	/*if (cvar.kz_ground_strafe)
		GroundStrafe(cmd);*/
		//if (cvar.kz_bhop)
		/*char p[10] = { 0 };
		itoa(pmove->flags, p, 10);
		OutputDebugStringA(std::string("pmove->flags:" + std::string(p)).data());*/
		//if(Bhop)

	if (AllGo)
	{
		AdjustSpeed(1.f);
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (BhopModul == false)
			{
				BHop(cmd);
			}
			else
			{
				//BHop3(cmd);
			}
		}
		if (GetAsyncKeyState(VK_MENU
		) && Start)
		{
			BHop2(cmd);
		}
	}
		//if (GetAsyncKeyState(VK_SPACE) && autotongbu)
		if (GetAsyncKeyState(VK_SPACE) && AllGo)   //F8连跳和同步一起开
			StrafeHack2(cmd);
		//if (GetAsyncKeyState(VK_MENU) && autotongbu)
		if (GetAsyncKeyState(VK_MENU) && AllGo)   //F8连跳和同步一起开
			StrafeHack2(cmd);
//		if (GetAsyncKeyState(0x43) && kakong)  //C卡空
//			AdjustSpeed(0.000001);
		if (GetAsyncKeyState(VK_SHIFT) && Mscj)
			StrafeHack2(cmd);
		if (GetAsyncKeyState(VK_SHIFT) && Mscj)
			GroundStrafeMSCJ(cmd);
		if (GetAsyncKeyState(0x57) && speed278)
			FastRun(cmd);
		if (GetAsyncKeyState(VK_MENU) && AllGo)
			BHop2(cmd);
		if (GetAsyncKeyState(0x38) && DTGL);                   // 8 地图高亮
		DTGL_();
		if (GetAsyncKeyState(VK_F5) && XXTS);                   //F5 显血名透视
		XXTS_();
		if (GetAsyncKeyState(0x5A) && QHZY);                   //z 切换显血名阵营
		QHZY_();
		if (GetAsyncKeyState(0x30) && DSRC);                   //7 第三人称
		DSRC_();
	}
}



//void Kz(float frametime, struct usercmd_s *cmd)
//{
//	if (g_Local.bAlive)
//	{
//		if (cvar.kz_strafe)
//			StrafeHack(frametime, cmd);
//		if (cvar.kz_fast_run)
//			FastRun(cmd);
//		if (cvar.kz_gstrafe)
//			GroundStrafe(cmd);
//		if (cvar.kz_bhop)
//			BHop(frametime, cmd);
//		if (cvar.kz_jump_bug)
//			JumpBug(frametime, cmd);
//	}
//	if (g_Local.bJumped && (g_Local.iFlags & FL_ONGROUND || g_Local.iMovetype == MOVETYPE_FLY))
//	{
//		Vector endpos = g_Local.vOrigin;
//		endpos.z -= g_Local.iUsehull == 0 ? 36.0 : 18.0;
//		g_Local.vT2 = endpos;
//		if (endpos.z == g_Local.vStartjumppos.z)
//		{
//			Vector lj = endpos - g_Local.vStartjumppos;
//			float dist = lj.Length() + 32.0625f + 0.003613;
//			if (dist >= 200)
//			{
//				InterpFps = FpsCount / FrameCount;
//				FpsCount = 0;
//				FrameCount = 0;
//				g_Local.flJumpdist = dist;
//				g_Local.flJumpmesstime = GetTickCount() + 10000;
//			}
//		}
//		g_Local.bJumped = false;
//	}
//	if (!g_Local.bJumped && (g_Local.iFlags & FL_ONGROUND) && cmd->buttons & IN_JUMP)
//	{
//		PreStrafe = g_Local.flVelocityspeed;
//		if (g_Local.flEdgeDistance != 250)
//			JumpOff = g_Local.flEdgeDistance;
//		else JumpOff = 0;
//		g_Local.vStartjumppos = g_Local.vOrigin;
//		g_Local.vStartjumppos.z -= g_Local.iUsehull == 0 ? 36.0 : 18.0;
//		g_Local.vT1 = g_Local.vStartjumppos;
//		g_Local.bJumped = true;
//	}
//	if (cmd->buttons & IN_FORWARD) { Keyforwardm = true; }
//	else { Keyforwardm = false; }
//	if (cmd->buttons & IN_MOVELEFT) { Keymoveleft = true; }
//	else { Keymoveleft = false; }
//	if (cmd->buttons & IN_MOVERIGHT) { Keymoveright = true; }
//	else { Keymoveright = false; }
//	if (cmd->buttons & IN_BACK) { Keyback = true; }
//	else { Keyback = false; }
//	if (cmd->buttons & IN_DUCK) { Keyduck = true; }
//	else { Keyduck = false; }
//	if (cmd->buttons & IN_JUMP) { Keyjump = true;; }
//	else { Keyjump = false; }
//}

void KzFameCount()
{
	if (g_Local.bJumped)
	{
		FrameCount += 1;
		FpsCount += (1 / g_Local.flFrametime);
	}
}

void DrawLongJump()
{
	float WindowBorderSize = ImGui::GetStyle().WindowBorderSize;
	ImGui::GetStyle().WindowBorderSize = 0.0f;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin("Longjump", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
	{
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiSetCond_Always);

		if (cvar.kz_show_kz && g_Local.bAlive && CheckDraw() && g_pEngine->GetMaxClients())
		{
			float ft1[2];
			float ft2[2];
			if (g_Local.flJumpmesstime > GetTickCount())
			{
				if (WorldToScreen(g_Local.vT1, ft1) && WorldToScreen(g_Local.vT2, ft2))
				{
					int ScreenX = ft1[0], ScreenY = ft1[1];
					ImGui::GetCurrentWindow()->DrawList->AddLine({ ft1[0] + 1, ft1[1] + 1 }, { ft2[0] + 1, ft2[1] + 1 }, black());
					ImGui::GetCurrentWindow()->DrawList->AddLine({ ft1[0], ft1[1] }, { ft2[0], ft2[1] }, green());
				}

				if (WorldToScreen(g_Local.vT1, ft1))
				{
					int label_size = ImGui::CalcTextSize("Start", NULL, true).x;
					int ScreenX = ft1[0], ScreenY = ft1[1];
					ImGui::GetCurrentWindow()->DrawList->AddRect({ (float)ScreenX - label_size / 2 - 2, (float)ScreenY - 23 }, { (float)ScreenX - label_size / 2 + label_size + 4, (float)ScreenY - 9 }, black(), cvar.visual_rounding);
					ImGui::GetCurrentWindow()->DrawList->AddRect({ (float)ScreenX - label_size / 2 - 3, (float)ScreenY - 24 }, { (float)ScreenX - label_size / 2 + label_size + 3, (float)ScreenY - 10 }, wheel1(), cvar.visual_rounding);
					ImGui::GetCurrentWindow()->DrawList->AddText({ (float)ScreenX - label_size / 2, (float)ScreenY - 25 }, white(), "Start");
				}

				if (WorldToScreen(g_Local.vT2, ft2))
				{
					int label_size = ImGui::CalcTextSize("Stop", NULL, true).x;
					int ScreenX = ft2[0], ScreenY = ft2[1];
					ImGui::GetCurrentWindow()->DrawList->AddRect({ (float)ScreenX - label_size / 2 - 2, (float)ScreenY - 23 }, { (float)ScreenX - label_size / 2 + label_size + 4, (float)ScreenY - 9 }, black(), cvar.visual_rounding);
					ImGui::GetCurrentWindow()->DrawList->AddRect({ (float)ScreenX - label_size / 2 - 3, (float)ScreenY - 24 }, { (float)ScreenX - label_size / 2 + label_size + 3, (float)ScreenY - 10 }, wheel1(), cvar.visual_rounding);
					ImGui::GetCurrentWindow()->DrawList->AddText({ (float)ScreenX - label_size / 2, (float)ScreenY - 25 }, white(), "Stop");
				}
			}
		}
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::GetStyle().WindowBorderSize = WindowBorderSize;
	}
}

void DrawKzKeys()
{
	int FontColor[] = { 100,100,255 };
	if (cvar.kz_show_kz && g_Local.bAlive && CheckDraw() && g_pEngine->GetMaxClients())
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.25f));
		ImGui::SetNextWindowPos(ImVec2(167, (ImGui::GetIO().DisplaySize.y / 2) - ImGui::GetIO().DisplaySize.y / 20 * 1), ImGuiCond_FirstUseEver);
		if (ImGui::Begin("kz-show-keys", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("%s", Keyforwardm ? "  W" : "  |");
			ImGui::Text("%s %s %s", Keymoveleft ? "A" : "-", Keyback ? "S" : "+", Keymoveright ? "D" : "-");
			ImGui::Text(Keyduck ? " Duck" : "  |");
			ImGui::Text(Keyjump ? " Jump" : "  |");

			ImGui::PopStyleColor();
			ImGui::End();
		}
	}
}

void DrawKzWindow()
{
	if (cvar.kz_show_kz && g_Local.bAlive && CheckDraw() && g_pEngine->GetMaxClients())
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.25f));
		ImGui::SetNextWindowPos(ImVec2(20, (ImGui::GetIO().DisplaySize.y / 2) - ImGui::GetIO().DisplaySize.y / 20 * 1), ImGuiCond_Once);
		ImGui::Begin("kz-show-kz", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
		{
			ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);
			ImVec4 col = col_default_text;

			static float fMaxPspeed = 0.f;
			if (g_Local.flVelocityspeed == 0)
				fMaxPspeed = 0.0;
			if (g_Local.flVelocityspeed > fMaxPspeed)
				fMaxPspeed = g_Local.flVelocityspeed;
			if (g_Local.flDamage >= g_Local.iHealthStrafe)
				col = ImColor(1.f, 0.f, 0.f, 1.0f);

			if (g_Local.flJumpmesstime > GetTickCount())
			{
				ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), "Time: %.1f", (g_Local.flJumpmesstime - GetTickCount()) / 1000);
				ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), "LongJump: %.3f", g_Local.flJumpdist);
				ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), "PreStrafe: %.3f", PreStrafe);
				ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), "JumpOff: %.3f", JumpOff);
				ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), "Fps: %.1f", InterpFps);
			}

			ImGui::Text("Speed: %.3f", g_Local.flVelocityspeed);
			ImGui::Text("SpeedMax: %.3f", fMaxPspeed);
			ImGui::Text("Height: %.3f", g_Local.flHeightorigin);
			ImGui::Text("FallSpeed: %.3f", g_Local.flFallVelocity);
			ImGui::Text("GroundAngle: %.3f", g_Local.flGroundangle);
			ImGui::TextColored(col, "Damage: %.1f", g_Local.flDamage);
			ImGui::TextColored(ImVec4(1.f, 0.f, g_Local.flEdgeDistance, 1.f), "Edge: %.3f", g_Local.flEdgeDistance);

			ImGui::PopStyleColor();
			ImGui::End();
		}
	}
}

inline float EndSpeed(float StartSpeed, float gravity, float frametime, float distance)
{
	while (distance > 0)
	{
		StartSpeed += gravity * frametime;
		float dist = StartSpeed * frametime;
		distance -= dist;
	}
	return StartSpeed;
}

inline float interp(float s1, float s2, float s3, float f1, float f3)
{
	if (s2 == s1)return f1;
	if (s2 == s3)return f3;
	if (s3 == s1)return f1;
	return f1 + ((s2 - s1) / (s3 - s1)) * ((f3 - f1)/*/1*/);
}

float Damage()
{
	Vector start = pmove->origin;
	vec3_t vForward, vecEnd;
	float va[3];
	g_Engine.GetViewAngles(va);
	g_Engine.pfnAngleVectors(va, vForward, NULL, NULL);
	vecEnd[0] = start[0] + vForward[0] * 8192; vecEnd[1] = start[1] + vForward[1] * 8192; vecEnd[2] = start[2] + vForward[2] * 8192;
	pmtrace_t* trace = g_pEngine->PM_TraceLine(start, vecEnd, 1, 2, -1);
	float fDistance = ((start.z) - (trace->endpos.z)) - (pmove->usehull == 0 ? (36) : (18));
	float endSpeed = EndSpeed(pmove->flFallVelocity, 800, 1 / 1000.0f, fDistance);
	if (interp(504.80001f, endSpeed, 1000, 1, 100) > 0)
		return interp(504.80001f, endSpeed, 1000, 1, 100);
	else return 0;
}

inline float EdgeDistance() {
#define TraceEdge(x,y){\
    Vector start=pmove->origin;\
	start[2]-=0.1f;\
	Vector end=start;\
	end[1]+=x*mind;\
	end[0]+=y*mind;\
	pmtrace_s* t1 = g_pEngine->PM_TraceLine(end,start,1,pmove->usehull,-1);\
	if(!(t1->startsolid))mind=(t1->endpos-start).Length2D();\
	}
	float mind = 250;
	TraceEdge(-1, 0);
	TraceEdge(1, 0);
	TraceEdge(0, 1);
	TraceEdge(0, -1);
	TraceEdge(-1, -1);
	TraceEdge(1, 1);
	TraceEdge(1, -1);
	TraceEdge(-1, 1);
	return mind;
}