function [emaxh,emaxv] = matrixdiff(a,b,a1,b1)
	eh = zeros(size(a)(1) * size(a)(2),1);
	for i = 1:size(a)(1)
		for j = 1:size(a)(2)
			eh((i-1)*size(a)(1) + j) = abs(a(i,j) - a1(i,j));			

		endfor
	endfor
	ev = zeros(size(b)(1) * size(b)(2),1);
	for i = 1:size(b)(1)
		for j = 1:size(b)(2)
			ev((i-1)*size(b)(1) + j) = abs(b(i,j) - b1(i,j));
		endfor
	endfor
	emaxh = max(eh);
	emaxv = max(ev);
endfunction
