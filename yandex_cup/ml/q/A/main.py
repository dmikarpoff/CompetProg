import json
import catboost
import random
import numpy as np

f = open("benjamin_dataset.json", "r")
raw_data = json.load(f)

data = []
labels = []

for sample in raw_data:
    label = sample["label"]
    labels.append(label)
    sample_data = [v for k, v in sample.items() if k != 'label']
    data.append(sample_data)

model = catboost.CatBoostClassifier(iterations=400,
                                    learning_rate=1.0,
                                    depth=5,
                                    l2_leaf_reg=10.0,
                                    rsm=0.75,
                                    border_count=60,
                                    max_ctr_complexity=10,
                                    random_strength=40.0,
                                    bagging_temperature=100.0,
                                    grow_policy="Depthwise",
                                    min_data_in_leaf=3,
                                    langevin=True,
                                    diffusion_temperature=100000,
                                    eval_metric='Accuracy')
model.fit(data, labels, plot=True)
print(model.get_best_score())
cv_params = model.get_params();
cv_params.update({'loss_function': 'Logloss', 'eval_metric': 'Accuracy'})
cv_data = catboost.cv(catboost.Pool(data, labels), cv_params, plot=True)
print('Precise validation accuracy score: {}'.format(np.max(cv_data['test-Accuracy-mean'])))
print("params = {}".format(cv_params))