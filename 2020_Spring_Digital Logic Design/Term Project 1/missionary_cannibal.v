module missionary_cannibal(missionary_curr, cannibal_curr, direction, missionary_next, cannibal_next);

	//Input declaration
	input[1:0]missionary_curr;
	input[1:0]cannibal_curr;
	input direction;
	output[1:0]missionary_next;
	output[1:0]cannibal_next;

	//Inner net definition
	wire w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15, w16, w17, w18;

	//Basic logic gate instantiation

	// w
	and (w1, missionary_curr[1], cannibal_curr[1], cannibal_curr[0]);//3-input and gate(acd)
	and (w2, missionary_curr[1], ~direction); //2-input and gate(ae')
	and (w3, ~missionary_curr[1], missionary_curr[0]);//2-input and gate(a'b)
	and (w4, missionary_curr[0],cannibal_curr[1]);//2-input and gate(bc)
	and (w5, ~missionary_curr[0], ~cannibal_curr[1], direction);//3-input and gate(b'c'e)
	and (w6, cannibal_curr[1], cannibal_curr[0], ~direction);//3-input and gate(cde')
	and (w7, ~cannibal_curr[1], ~cannibal_curr[0]);//2-input and gate(c'd')
	or w(missionary_next[1],w1, w2, w3, w4, w5, w6, w7); 

	// x
	and (w8, missionary_curr[1], cannibal_curr[0]);//2-input and gate(ad)
	and (w9, ~cannibal_curr[1], direction);//2-input and gate(c'e)
	or x(missionary_next[0],w8, w2, w4, w6, w7, w9);
	
	//y
	and (w10, missionary_curr[1], ~missionary_curr[0]);//2-input and gate(ab')
	and (w11, ~missionary_curr[0], ~cannibal_curr[1]);//2-input and gate(b'c')
	and (w12, cannibal_curr[1], ~direction);//2-input and gate(ce')
	and (w13, ~cannibal_curr[1], ~cannibal_curr[0], direction);//3-input and gate(c'd'e)
	and (w14, cannibal_curr[0], ~direction);//2-input and gate(de')
	or y(cannibal_next[1],w10, w3, w11, w12, w13, w14);

	
	//z

	and (w15, missionary_curr[1], ~missionary_curr[0], cannibal_curr[0]);//3-input and gate(ab'd)
	and (w16, ~missionary_curr[1], missionary_curr[0],
	cannibal_curr[1]);//3-input and gate(a'bc)
	and (w17, cannibal_curr[1], cannibal_curr[0]);//2-input and gate(cd)
	and (w18, ~cannibal_curr[0], ~direction);//2-input and gate(d'e')	
	or z(cannibal_next[0], w15, w16, w17, w9, w18);

endmodule
