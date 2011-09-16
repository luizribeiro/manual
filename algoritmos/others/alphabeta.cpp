function alphabeta(node, depth, alpha, beta, Player)
	if depth == 0 or node is a terminal node
		return the heuristic value of node
	if Player == MaxPlayer
		for each child of node
			alpha = max(alpha, alphabeta(child, depth-1, alpha, beta, not(Player)))
			if beta <= alpha
				break                             (* Beta cut-off *)
		return alpha
	else
		for each child of node
			beta = min(beta, alphabeta(child, depth-1, alpha, beta, not(Player)))
			if beta <= alpha
				break                             (* Alpha cut-off *)
		return beta
(* Initial call *)
alphabeta(origin, depth, -infinity, +infinity, MaxPlayer)
