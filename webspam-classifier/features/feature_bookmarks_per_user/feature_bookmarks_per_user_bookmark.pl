my %table;

open(TAS_SPAM,"tas") or die "cant open TAS_SPAM: $!";
open(TSPAM,">NONSPAM") or die "cant open TSPAM: $!";

while(<TAS_SPAM>){
	chomp;
	my ($user_id , $tag , $content_id, $content_val ,$date) = split /\s+/;
	push @{$table{$user_id}},$content_id;
}

foreach $user_id (sort {$a <=> $b } keys %table){
	
		if ( $user_id % 3 == 0 && $user_id != 0) {
		
		@values = @{$table{$user_id}};
		$count = @values;		
		
			print "$user_id (@values) (7:$count)\n\n\n\n";
		
			print TSPAM "$user_id (@values) (7:$count)\n\n\n\n"; 
		}
		

}

close(TAS_SPAM);
close(TSPAM);

