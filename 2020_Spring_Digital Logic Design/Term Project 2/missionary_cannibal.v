module missionary_cannibal(clk, reset, missionary_next, cannibal_next, finish);
	input clk;
	input reset;
	output reg [1:0] missionary_next;
	output reg [1:0] cannibal_next;
	output reg finish;

	parameter s0 = 4'b1111, 
	s1 = 4'b1101, 
	s2 = 4'b1110, 
	s3 = 4'b1100, 
	s5 = 4'b0101, 
	s6 = 4'b1010, 
	s7 = 4'b0010, 
	s8 = 4'b0011, 
	s9 = 4'b0001,
	s11 = 4'b0000;

	reg direction; 
	reg[3:0] current_state,next_state; 

	always @ (posedge clk or posedge reset) 
	begin 
    	if(reset) direction <= 1'b0;
    	else direction <= ~direction;
  	end
	
	always @(posedge clk or posedge reset)
	begin
		if(reset) begin
			current_state <= s0;
		end
		else begin
			current_state <= next_state;
		end
	end
	
	
	always @(posedge clk or posedge reset)
	begin 
		if(reset) begin
			missionary_next <= 2'b11; 
			cannibal_next <= 2'b01;
			finish <= 0;
		end
		else begin
			case(next_state)
				s0: begin missionary_next <= 2'b11; cannibal_next <= 2'b11; finish <= 0; end
				s1: begin missionary_next <= 2'b11; cannibal_next <= 2'b01; finish <= 0; end
				s2: begin missionary_next <= 2'b11; cannibal_next <= 2'b10; finish <= 0; end
				s3: begin missionary_next <= 2'b11; cannibal_next <= 2'b00; finish <= 0; end
				s5: begin missionary_next <= 2'b01; cannibal_next <= 2'b01; finish <= 0; end
				s6: begin missionary_next <= 2'b10; cannibal_next <= 2'b10; finish <= 0; end
				s7: begin missionary_next <= 2'b00; cannibal_next <= 2'b10; finish <= 0; end
				s8: begin missionary_next <= 2'b00; cannibal_next <= 2'b11; finish <= 0; end
				s9: begin missionary_next <= 2'b00; cannibal_next <= 2'b01; finish <= 0; end
				s11: begin missionary_next <= 2'b00; cannibal_next <= 2'b00; finish <= 1; end
				default	: begin missionary_next <= 2'b11; cannibal_next <= 2'b11; finish <= 0; end
			endcase
		end
	end
	
	always @( * )
	begin 
		case(current_state)
			s0: begin next_state = s1; end
			s1: begin if(direction) next_state = s2; else next_state = s5; end
			s2: begin next_state = s3; end
			s3: begin next_state = s1; end
			s5: begin next_state = s6; end
			s6: begin next_state = s7; end
			s7: begin if(direction) next_state = s8; else next_state = s11; end
			s8: begin next_state = s9; end
			s9: begin next_state = s7; end
			s11: begin next_state = s0; end
			default	: begin next_state = s0; end
		endcase
	end
endmodule 