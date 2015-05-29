-----------------------------------
-- PP-2 Lab 6                    --
-- Lab 6: Ada. Protected modules --
-- Guk Alexander                 --
-- IP-22                         --
-- 21.05.2015                    --
-----------------------------------

with Ada.Text_IO;
use Ada.Text_IO;

with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;

with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;

procedure lab6 is
 	N: integer := 4000;
	P: integer := 8;
	H: integer := N / p;
	Value: Integer := 1;

	type Vector is array (1..N) of integer;
	type Matrix is array (1..N) of Vector;

	MA, MO, MT, MR: Matrix;
	Z, B, C: Vector;

	procedure Input_Vector(V : out Vector) is
	begin
		for i in 1..N loop
			V(i) := Value;
		end loop;
	end Input_Vector;

	procedure Input_Matrix(M : out Matrix) is
	begin
		for i in 1..N loop
			Input_Vector(M(i));
		end loop;
	end Input_Matrix;

	procedure Output_Vector(V : in Vector) is
	begin
		for i in 1..N loop
			Put(V(i));
		end loop;
		New_Line;
	end Output_Vector;

	procedure Output_Matrix(M : in Matrix) is
	begin
		for i in 1..N loop
			Output_Vector(M(i));
		end loop;
		New_Line;
	end Output_Matrix;

	function calculateMaxH(beginL, EndL : in Integer) return integer is
		max: Integer:= Z(beginL+1);
	begin	
		for i in BeginL + 2..EndL loop
			if Z(i) > max then
				max:= Z(i);
			end if;
		end loop;
		return max;
	end calculateMaxH;
	
	function calculateBCh(beginL, EndL : in Integer) return integer is
		result: Integer:= 0;
	begin	
		for i in BeginL+1..EndL loop
			result:= result + B(i) * C(i);
		end loop;
		return result;
	end calculateBCh;

	procedure calculateMAh(Maxx, tx : in Integer; MTx : in matrix;  beginL, endL : in Integer) is
		tmpM : Matrix;
	begin	
    	for i in beginL+1..endL loop
            for j in 1..N loop
				tmpM(J)(I) := MO(J)(I) * maxx;
			end loop;
		end loop;
	
    	for i in beginL+1..endL loop
            for j in 1..N loop
				MA(J)(I) := 0;
	            for k in 1..N loop
					MA(J)(I) := MA(J)(I) + MTx(J)(K) * MR(k)(i);
				end loop;
				mA(j)(i) := mA(J)(I) * tx;
				MA(J)(I) := MA(J)(I) + tmpM(J)(I);
			end loop;
		end loop;
	end calculateMAh;

	protected Control is
		entry Wait_input;
		entry wait_Calculate1;
		entry wait_Calculate2;

		function Copy_Max return integer;
		function Copy_T return integer;
 		function Copy_MT return Matrix;
 
 		procedure Write_Max(Max1: in Integer);
 		procedure Write_T(T1: in integer);
 		procedure Write_MT(MT1: in Matrix);
 
 		procedure Signal_of_Input;
 		procedure Signal_of_Calculate1;
 		procedure Signal_of_Calculate2;
 		private			
 			NUM_OF_INPUTS: integer:= 3;
 			NUM_OF_CALCS_1: integer:= P;
 			NUM_OF_CALCS_2: integer:= P - 1;
 			FlagInput: Integer:= 0;
 			flagCalculate1: Integer:= 0;
 			flagCalculate2: Integer:= 0;
 
 			max: Integer:= -999999;
 			T: Integer:= 0;
 	end Control;
 	
 	protected body Control is
 		entry Wait_input when FlagInput = NUM_OF_INPUTS is
 		begin
 			null;
 		end Wait_input;
 		entry wait_Calculate1 when flagCalculate1 = NUM_OF_CALCS_1 is
 		begin
 			null;
 		end wait_Calculate1;
 		entry wait_Calculate2 when flagCalculate2 = NUM_OF_CALCS_2 is
 		begin
 			null;
 		end wait_Calculate2;
 
 		function Copy_Max return integer is
 		begin
 			return max;
 		end Copy_Max;
 		function Copy_T return integer is
 		begin
 			return T;
 		end Copy_T;
 		function Copy_MT return Matrix is
 		begin
 			return mT;
 		end Copy_MT;
 
 		procedure Write_Max(Max1: in Integer) is
 		begin
 			if Max1 > Max then
 				Max := Max1;
 			end if;
 		end Write_Max;
 		procedure Write_T(T1: in integer) is
 		begin
 			T:= T + T1;
 		end Write_T;
 		procedure Write_MT(MT1: in Matrix) is
 		begin
 			MT:= MT1;
 		end Write_MT;
 
 		procedure Signal_of_Input is
 		Begin
 			FlagInput:= FlagInput + 1;
 		end Signal_of_Input;
 		procedure Signal_of_Calculate1 is
 		begin
 			flagCalculate1:= flagCalculate1 + 1;
 		end Signal_of_Calculate1;
 		procedure Signal_of_Calculate2 is
 		begin
 			flagCalculate2:= flagCalculate2 + 1;
 		end Signal_of_Calculate2;
 	end Control;
 
 -----------------------------------------------------
 
 	Task T1;
     task BODY t1 IS
 		max1, t1: Integer;
		MT1: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 0 * H;
 		endL:= beginL + H;
 		put_line("Process T1 started");
 		
 		input_matrix(MO);

		Control.Signal_Of_Input;
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max1:= Control.Copy_Max;
 		t1:= Control.Copy_T;
 		MT1:= Control.Copy_MT;
 		calculateMAh(max1, t1, MT1, beginL, endL);
 
 		Control.Wait_Calculate2;

		Output_Matrix(MA);

 		put_line("Process T1 finished");
 	end T1;
 	-----------------------------------------------------
 
 	Task T2;
     task BODY t2 IS
 		max2, t2: Integer;
		MT2: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 1 * H;
 		endL:= beginL + H;
 		put_line("Process T2 started");
 
 		input_matrix(MR);
 		input_Vector(B);
 		input_Vector(Z);

		Control.Signal_Of_Input;
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max2:= Control.Copy_Max;
 		t2:= Control.Copy_T;
 		MT2:= Control.Copy_MT;
 		calculateMAh(max2, t2, MT2, beginL, endL);
 
 		Control.Signal_Of_Calculate2;

 		put_line("Process T2 finished");
 	end T2;
 	-----------------------------------------------------
 
 	Task T3;
     task BODY t3 IS
 		max3, t3: Integer;
		MT3: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 2 * H;
 		endL:= beginL + H;
 		put_line("Process T3 started");
 
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max3:= Control.Copy_Max;
 		t3:= Control.Copy_T;
 		MT3:= Control.Copy_MT;
 		calculateMAh(max3, t3, MT3, beginL, endL);
 
 		Control.Signal_Of_Calculate2;

 		put_line("Process T3 finished");
 	end T3;
 	-----------------------------------------------------
 
 	Task T4;
     task BODY t4 IS
 		max4, t4: Integer;
		MT4: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 3 * H;
 		endL:= beginL + H;
 		put_line("Process T4 started");
 
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max4:= Control.Copy_Max;
 		t4:= Control.Copy_T;
 		MT4:= Control.Copy_MT;
 		calculateMAh(max4, t4, MT4, beginL, endL);
 
 		Control.Signal_Of_Calculate2;

 		put_line("Process T4 finished");
 	end T4;
 	-----------------------------------------------------
 
 	Task T5;
     task BODY t5 IS
 		max5, t5: Integer;
		MT5: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 4 * H;
 		endL:= beginL + H;
 		put_line("Process T5 started");
 
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max5:= Control.Copy_Max;
 		t5:= Control.Copy_T;
 		MT5:= Control.Copy_MT;
 		calculateMAh(max5, t5, MT5, beginL, endL);
 
 		Control.Signal_Of_Calculate2;

 		put_line("Process T5 finished");
 	end T5;
 -----------------------------------------------------
 
 	Task T6;
     task BODY t6 IS
 		max6, t6: Integer;
		MT6: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 5 * H;
 		endL:= beginL + H;
 		put_line("Process T6 started");

		input_matrix(MT);
 		input_Vector(C);

		Control.Signal_Of_Input;
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max6:= Control.Copy_Max;
 		t6:= Control.Copy_T;
 		MT6:= Control.Copy_MT;
 		calculateMAh(max6, t6, MT6, beginL, endL);
 
 		Control.Signal_Of_Calculate2;

 		put_line("Process T6 finished");
 	end T6;
 	-----------------------------------------------------
 
 	Task T7;
     task BODY t7 IS
 		max7, t7: Integer;
		MT7: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 6 * H;
 		endL:= beginL + H;
 		put_line("Process T7 started");
 
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max7:= Control.Copy_Max;
 		t7:= Control.Copy_T;
 		MT7:= Control.Copy_MT;
 		calculateMAh(max7, t7, MT7, beginL, endL);
 
 		Control.Signal_Of_Calculate2;

 		put_line("Process T7 finished");
 	end T7;
 	-----------------------------------------------------
 
 	Task T8;
     task BODY t8 IS
 		max8, t8: Integer;
		MT8: Matrix;

		maxH, BCh, BeginL, endL: Integer;
 	begin
 		beginL:= 7 * H;
 		endL:= beginL + H;
 		put_line("Process T8 started");
 
 		Control.Wait_Input;
 
 		maxH:= calculateMaxH(beginL, endL);
 		Control.Write_Max(maxH);
 		BCh:= CalculateBCh(beginL, endL);
 		Control.Write_T(BCh);
 
 		Control.signal_of_Calculate1;
 		Control.Wait_Calculate1;
 
 		Max8:= Control.Copy_Max;
 		t8:= Control.Copy_T;
 		MT8:= Control.Copy_MT;
 		calculateMAh(max8, t8, MT8, beginL, endL);
 
 		Control.Signal_Of_Calculate2;

 		put_line("Process T8 finished");
 	end T8;
 
 begin
 	put_line("Main process started");
 end lab6;


