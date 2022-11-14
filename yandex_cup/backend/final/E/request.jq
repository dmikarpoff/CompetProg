jq --indent 4  // indent 4
    -S         // sort keys
    -M         // monochrome output
    --argjson ourEmployee ${OUR_EMPLOYEE}  // replaced in request  
’
[  // wrap in array
    .[]  // iterate over array 
    | 
    {
        description: ."base-info"?.description,
        index,       
        reviewers: (
            try (
                [
                    .reviewers[] | ..|.name? |  select(. != null)
                ] 
                | unique - $ourEmployee
            ) 
            catch []
        ),     
        works: (
            try 
                [
                    .works[] 
                    | 
                    {
                        (.author): .charters[]
                    }
                ] 
            catch []
        ),  
        authors: [.author, ."co-authors"[]?], 
        range:[.values[-1,0]?],  
        cost:((.time[-1]-.time[0]-0?) * (.price // 5)),  
        reviewer: ."base-info"? | . | .["reviewer.name"],  
        last: [.results[-1]?.url],
        remains: [.results[:-1][]?.url]
    }
]  // end of wrap in array
’