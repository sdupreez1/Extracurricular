library(vcfR)
  # to load .vcf files
library(circlize)
library(tidyr)
library(dplyr)
library(stringr)
library(ggplot2)

setwd(
  "C:/Users/sethd/OneDrive/Documents/Programming/Bioinformatics Work Exp/data"
)

# Data Wrangling and Exploration
m.vcf = read.vcfR('mutect2.mutect2.10.forSeth.vcf')

pgen = read.csv('MITOMAP.csv')
  # pathogenic variants

pgen.vars = pgen |>
  mutate(Mutation = str_extract(Allele, "[^0-9]*$"),
         Allele = str_extract(Allele, '[0-9].*$'))
  # [^0-9] means anything but (^) numbers, * means 0 or more characters, 
  # $ means to the end

  # whole regex matches all characters from the end until the first number is 
  # reached

npgenic = nrow(pgen.vars)



m.dirtyf = data.frame(m.vcf@fix, m.vcf@gt)

m.df = m.dirtyf |> 
  filter((FILTER == 'PASS') & 
           (substr(SAMPLE,start=nchar(SAMPLE), stop=nchar(SAMPLE))) != 'B' &
           REF != ALT)

npatients = length(unique(m.df$SAMPLE))
  # 10 patients

m.vnts = m.df |> 
  mutate(MUTATION = paste(REF, ALT, sep = '>'))
  
#info.split = for(i in 1:n(m.df$INFO)){
#  for(j in 1:str_count(m.df$INFO, ';')[i]){
#    str_split_i(m.df$INFO)[[j]]
#  }
#}

#m.vnts.info = m.vnts |>
# mutate()

m.freq = m.vnts |>
  group_by(POS, MUTATION) |>
  summarise(FREQ = n()) |> 
  mutate(AF = FREQ/npatients) |>
  mutate(PGENIC = as.factor(
    ifelse(str_c(POS, MUTATION) %in% pgen.vars$Allele, 1, 0))
    )
  

nvnts = nrow(m.freq)
# 103 uniquely positioned variants


m.freq.by_pos = m.vnts |>
  group_by(POS) |>
  summarise(FREQ = n())

# nrow(m.freq.by_pos) = nrow(m.freq) = 103, so there are no two variants with
# the same position







# Comparison Data
ukbb = read.table('ukbb_freqM.txt', header = TRUE) |> filter(pop == 'EUR')

bb.split = data.frame(chrom = str_split_i(ukbb$variant, ':', i=1),
                      POS = str_split_i(ukbb$variant, ':', i=2),
                      MUTATION = str_replace(
                        str_split_i(ukbb$variant, ':', i=3),
                        ',', '>'))  
# gets the ukbb data in comparable form to vcf, turning the comma into a space 
# is to match the form of mutation in the m data

ukbb.vnts = ukbb |> rename(MUTATION = variant) |>
  mutate(chrom = bb.split$chrom, 
         POS = bb.split$POS, 
         MUTATION = bb.split$MUTATION, 
         .before = MUTATION)

n.ukbb = round(mean(ukbb.vnts$N/ukbb.vnts$AF, na.rm = TRUE))
# AF = N/total, so total = N/AF, but due to rounding errors, there will be
# some error, so we take the mean to be our total n in the ukbb sample

ukbb.freq = ukbb.vnts[,c('POS', 'MUTATION', 'N', 'AF')] |>
  mutate(PGENIC = as.factor(
    ifelse(str_c(POS, MUTATION) %in% pgen.vars$Allele, 1, 0))
  )


ukbb.compare = ukbb.freq |> 
  semi_join(m.freq, by = c('POS', 'MUTATION'))
  # returns all rows in ukbb where both POS and MUTATION match a row in m.

filter(m.freq, !POS %in% unique(ukbb.compare$POS))
  # this was the only variant which was in our m. and not in ukbb

  # did cause issues when the T>T mutation was included, but now there are 
  # no differences between the two dfs

ukbb.compare = arrange(ukbb.compare, POS)
m.freq = arrange(m.freq, POS)

# arrange() so that POS matches in both data sets



# Bar Plot of mutation against position
ggplot(mapping = aes(POS, AF, fill = PGENIC)) + 
  geom_col(data = m.freq[1:35,]) + ylim(0,1) +
  geom_point(aes(col = PGENIC), data = ukbb.compare[1:35,]) +
  theme(axis.text.x = element_text(angle = 45, hjust = 1, size = 7.5)) +
  scale_fill_manual(values = c('0' = 'slategray4',
                                '1' = 'brown1')) +
  scale_color_manual(values = c('0' = 'darkturquoise',
                                '1' = 'darkred'))

ggplot(mapping = aes(POS, AF, fill = PGENIC)) + 
  geom_col(data = m.freq[36:70,]) + ylim(0,1) +
  geom_point(aes(col = PGENIC), data = ukbb.compare[36:70,]) +
  theme(axis.text.x = element_text(angle = 45, hjust = 1, size = 7.5)) +
  scale_fill_manual(values = c('0' = 'slategray4',
                               '1' = 'brown1')) +
  scale_color_manual(values = c('0' = 'darkturquoise',
                                '1' = 'darkred'))
ggplot(mapping = aes(POS, AF, fill = PGENIC)) + 
  geom_col(data = m.freq[71:103,]) + ylim(0,1) +
  geom_point(aes(col = PGENIC), data = ukbb.compare[71:103,]) +
  theme(axis.text.x = element_text(angle = 45, hjust = 1, size = 7.5)) +
  scale_fill_manual(values = c('0' = 'slategray4',
                               '1' = 'brown1')) +
  scale_color_manual(values = c('0' = 'darkturquoise',
                                '1' = 'darkred'))
  # multiple plots for legibility







# Scatter plot of UKBB AF against sample AF
ukbb.compare_posnum = ukbb.compare |> 
  mutate(POS = as.numeric(POS)) |>
  arrange(POS)

m.freq_posnum = m.freq |> 
  mutate(POS = as.numeric(POS)) |>
  arrange(POS)

  # arrange() so that when AF is combined in afplot the rows are the positions
  # in order

afplot = data.frame(POS = ukbb.compare_posnum$POS,
                    sampleAF = m.freq_posnum$AF,
                    ukbbAF = ukbb.compare_posnum$AF,
                    PGENIC = ukbb.compare_posnum$PGENIC)

pgenic.pos = c(sample(afplot$POS, 10))
  # add positions of variants to remove to compare corrs in the plot
  # currently just takes 10 random variants

afplot.nopgen = afplot |>
  filter(!POS %in% pgenic.pos)

lmodel = lm(sampleAF ~ ukbbAF, afplot)
lmodel.summ = summary(lmodel)

noP_lmodel = lm(sampleAF ~ ukbbAF, afplot.nopgen)
noP_lmodel.summ = summary(noP_lmodel)

cor(afplot$sampleAF, afplot$ukbbAF)

ggplot(afplot, aes(ukbbAF, sampleAF, col = PGENIC)) +
  geom_point() +
  geom_abline(slope = lmodel$coefficients[2], 
              intercept = lmodel$coefficients[1]) +
  geom_abline(slope = noP_lmodel$coefficients[2],
              intercept = noP_lmodel$coefficients[1],
              col = 'red')

in1sd = c(lmodel$coefficients[2] - lmodel.summ$coefficients[2,2] <=
                  noP_lmodel$coefficients[2] &
                  noP_lmodel$coefficients[2] <=
                  lmodel$coefficients[2] + lmodel.summ$coefficients[2,2])
  # returns TRUE or FALSE depending on if the noP model has a slope who's value
  # is within 1 sd of the slope of the full data model


all.cor = lmodel.summ$r.squared
noP.cor = noP_lmodel.summ$r.squared
corr.diff = lmodel.summ$r.squared - noP_lmodel.summ$r.squared
  # difference in linear correlation between whole data and noP data

# could make a loop to compare removal of all possible combinations of pgenic 
# variants







# Comparison
vnt.compare = data.frame(POS = m.freq$POS,
                         sampleAF = m.freq$AF,
                         popAF = ukbb.compare$AF,
                         resid = m.freq$AF - ukbb.compare$AF,
                         resid.sq = (m.freq$AF - ukbb.compare$AF)^2)


MSE = sum(vnt.compare$resid.sq)/nrow(vnt.compare)
# Mean square Error is less than 1/100 of the max value so a clear 
# relationship is present (as expected) between sample and population data

# [where the population is the mtDNA variants of all people in ukbb data]




# Circos Plots
pgen.vars = pgen.vars |>
  rename(POS = Position) |>
  mutate(POS = as.numeric(POS))

sample.pgen = semi_join(m.freq_posnum, pgen.vars, by = 'POS')

ukbb.vnts = mutate(ukbb.vnts, POS = as.numeric(POS))
ukbb.pgen = semi_join(ukbb.vnts, pgen.vars, by = 'POS')

circos.initializeCircularGenome('mtDNA', 16569, axis.labels.cex = 0.7)
circos.track(ylim = c(0,1), # ONLY FEED Y VALUES INTO PANEL.FUN, NOT HERE
               panel.fun = function(x,y){
                 circos.barplot(value=m.freq$AF, 
                                pos=as.numeric(m.freq$POS),
                                col = m.freq$PGENIC)
                 circos.points(x = as.numeric(sample.pgen$POS),
                               y = rep(1, nrow(sample.pgen)),
                               col = 'red')
               })
circos.track(ylim = c(0,1), bg.col = 'limegreen',
            panel.fun = function(x,y) {
              circos.barplot(value=ukbb.freq$AF,
                             pos=as.numeric(ukbb.freq$POS))
              circos.points(x = as.numeric(ukbb.pgen$POS),
                            y = rep(1, nrow(ukbb.pgen)),
                            col = 'red')
            })
circos.track(ylim = c(0, 1), bg.col = 'lightcoral', panel.fun = function(x, y) {
  circos.barplot(value=rep(1, npgenic), 
                 pos=pgen.vars$POS)
})
text(0, 1.01, 
     labels = 'Variant Frequency against Position and Pathogenic Variants', 
     cex = 0.8)

circos.clear()


