static bool binaryOutcomeGivenProbability(float probability)
{
    if(probability<=0){return(false);}
    if(probability>=1){return(true);}
    int size_of_random = 10000;
    int value = arc4random_uniform(size_of_random);
    bool outcome = false;
    int conversion_of_probability=0;
    float conversion_float = probability*size_of_random;
    conversion_of_probability = floor(conversion_float);
    if(value<=conversion_of_probability)
    {
        outcome=true;
    }
    return(outcome);
}


static int * squidGame(int trials, int players, int steps, float probability_each_step)
{
    if((trials<=0) || (players<=0) || (steps <=0) || (probability_each_step<0) || (probability_each_step>1))
    { return (NULL);}
    int *total_deaths=malloc(sizeof(int)*trials);
    memset(total_deaths,0,sizeof(int)*trials);
    int *total_survivors=malloc(sizeof(int)*trials);
    memset(total_survivors,0,sizeof(int)*trials);
    int trial_counter = 0;
    while(trial_counter<trials)
    {
        int *knowledge=malloc(sizeof(int)*steps);
        memset(knowledge,0,sizeof(int)*steps);
        int i=0;
        int deaths_in_trial=0;
        int survivors_in_trial=0;
        while(i<players)
        {
            bool alive = true;
            int step_counter = 0;
            while( (step_counter<steps) && (alive))
            {
                if(knowledge[step_counter]==0)
                {
                    bool reach_next_step = binaryOutcomeGivenProbability(probability_each_step);
                   
                    if(reach_next_step==false)
                    {
                        alive=false;
                    }
                    knowledge[step_counter]=1;
                }
                step_counter++;
            }
            if(alive==false)
            {
                total_deaths[trial_counter]++;
                deaths_in_trial++;
            }
            else
            {
                total_survivors[trial_counter]++;
                survivors_in_trial++;
            }
            i++;
        }
        trial_counter++;
        if(knowledge!=nil){free(knowledge);knowledge=nil;}
    }
    int *summary_vec_times_n_players_survived = malloc(sizeof(int)*(players+1));
    memset(summary_vec_times_n_players_survived,0,sizeof(int)*(players+1));
    
    int i=0; 
    int max_position_tracker_in_survival_vector=(players+1);//position = # times X number of people survived
    
    while (i< max_position_tracker_in_survival_vector)
    {
        int trial_tracker = 0;
        while(trial_tracker<trials)
        {
            if(total_survivors[trial_tracker] == i)
            {
                summary_vec_times_n_players_survived[i]++;
            }
            trial_tracker++;
        }
        i++;
    }
    
    if(total_deaths!=nil){free(total_deaths);total_deaths=nil;}
    if(total_survivors!=nil){free(total_survivors);total_survivors=nil;}
    return (summary_vec_times_n_players_survived);
    
}

-(void)main
{
    int players = 16, steps = 18, trials = 1000000;
    int *number_of_times_n_survived = squidGame(trials,players,steps,.5);
    
    if(number_of_times_n_survived!=nil)
    {
        int i=0;
        while(i<(players+1))
        {
            float odds=(float)number_of_times_n_survived[i]/(float)trials;//i'm paranoid ok?
            printf("Number of times %d players survived | %d | Probability: %f\n",i,number_of_times_n_survived[i],odds);
            i++;
        
        }
        free(number_of_times_n_survived);number_of_times_n_survived=NULL;
        return;
    }
}
