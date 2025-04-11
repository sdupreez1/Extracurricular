import re


# 1 - Counting DNA Nucleotides
s1 = open('rosalind_dna.txt', 'r').read()

dna_bases = ['A', 'C', 'G', 'T']
dna_to_rna = {'A':'u', 'C':'g', 'G':'c', 'T':'a'}

def base_count(s):
    return [s.count(base) for base in dna_bases]

s1_count = base_count(s1)
print(s1_count)

# 2 - Transcribing DNA into RNA
s2 = open('rosalind_rna.txt', 'r').read()

def transcribe(s):
    for base in dna_bases:
        s = s.replace(base, dna_to_rna[base])
    s = s.upper()
    return s

s2_rna = transcribe(s2)
print(s2_rna)

# 3 - Complementing a Strand of DNA
s3 = open('rosalind_revc.txt', 'r').read()

dna_c_bases = {'A':'t', 'C':'g', 'G':'c', 'T':'a'}

def dna_c(s):
    for base in dna_bases:
        s = s.replace(base, dna_c_bases[base])
    return s.upper()[::-1]  # slice that steps by -1 ('abcd'[::2] returns 'ac')

s3_c = dna_c(s3)
print(s3_c)

# 4 - Rabbits and Recurrence Relations
def fib(n):
    if n>2:
        return fib(n-1) + fib(n-2)
    return 1
print(fib(3))

# 5 - Computing GC Content
s5 = open('rosalind_gc.txt', 'r').read()

# Line 53-57 To process FASTA format things
s5_split = s5.split('>')[1:]
s5_labels = re.findall('Rosalind_[0-9]{4}', s5)[1:]

s5_str = [re.findall('(?<=Rosalind_[0-9]{4}).*', x.replace('\n', '')) for x in s5_split]
s5_str = [s[0] for s in s5_str]

def gc_percent(s):
    return 100*s.replace('G', 'C').count('C')/len(s)

s5_gc = [gc_percent(s) for s in s5_str]
whichmaxgc = s5_gc.index(max(s5_gc))

print(s5_labels[whichmaxgc], max(s5_gc))

# 6 - Counting Point Mutations
def d_H(s,t):
    return sum(s_i != t_i for s_i, t_i in zip(s,t))

# 8 - Translating RNA into Protein
s8 = open('rosalind_prot.txt', 'r').read()[:-1]

rna_to_aa = open('codon_to_aa.txt', 'r').read().split()
rna_to_aa = {codon:aa for codon, aa in zip(rna_to_aa[::2], rna_to_aa[1::2])}

def translate(s):
    return ''.join([rna_to_aa[codon] for codon in  list(map(''.join, zip(*[iter(s)]*3)))])

s8_prot = translate(s8)



